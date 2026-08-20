#include "pch.h"
#include "GameScene.h"
#include "InputManager.h"
#include "UIManager.h"
#include "Tower.h"
#include "Obstacle.h"
#include "PoolManager.h"
#include "TowerFactory.h"
#include "ObstacleFactory.h"
#include "SaveManager.h"
#include "Game.h"
#include "AudioManager.h"
#include "AudioManager.h"
#include "SceneManager.h"

namespace
{
	constexpr float kGameOverFadeDuration = 0.4f; // 게임오버 딤이 다 어두워지기까지 걸리는 시간(초)
	constexpr float kVictoryFadeDuration = 0.4f;  // 승리 딤이 다 어두워지기까지 걸리는 시간(초)
}

void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);
	_graphicRef = &graphic;

	ResourceManager& res = ResourceManager::GetInstance();

	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");

	_map.SetTileImages(&res.GetImage(L"Resource\\Tile\\Tile1_pipo.png"), &res.GetImage(L"Resource\\Tile\\Tile2_pipo.png"));
	if (_hasPendingLoad)
		_map.Init(&_pendingLoadData.startCell, &_pendingLoadData.endCell);
	else
		_map.Init();

	PoolManager::GetInstance().Init(250, 200, 50, 50, 250); // obstacleSize=50, effectSize=250: 임시값
	_waveManager.Init(&PoolManager::GetInstance().GetBloonPool(), _map.GetBloonSpawnPos(), _map.GetPathPtr(), this,
		[this](int32 bonusGold) { _economyManager.Add(bonusGold); SaveToFile(kSaveFilePath); });
	_healthManager.Init(_hasPendingLoad ? _pendingLoadData.hp : 150);
	_economyManager.Init(_hasPendingLoad ? _pendingLoadData.gold : 650);

	GetCollisionManager().RegisterLayer(RenderLayer::Bloon, RenderLayer::Projectile);

	_speedEnabled = _hasPendingLoad ? _pendingLoadData.speedEnabled : false;
	_isSettingsOpen = false;
	_gameOverFadeTimer = 0.0f;
	_isVictoryOpen = false;
	_victoryPopupShown = false;
	_victoryFadeTimer = 0.0f;
	UIManager::GetInstance().SetInputLocked(false); // 이전 판(게임오버 등)에서 잠긴 입력을 새 판 시작 시 반드시 풀어준다.
	AudioManager::GetInstance().SetBgmVolumeScale(1.0f);

	AudioManager::GetInstance().PlayBgm(L"jazz");

	if (_hasPendingLoad)
	{
		_waveManager.SetNextRound(_pendingLoadData.nextRound);
		_waveManager.SetAutoPlay(_pendingLoadData.autoPlay);

		const int32 gridSize = _map.GetGridSize();

		for (const TowerSaveData& towerData : _pendingLoadData.towers)
		{
			if (_map.TryOccupyCell(towerData.cell) == false)
				continue;
			Tower* tower = TowerFactory::Create(PoolManager::GetInstance().GetTowerPool(), towerData.type,
				Vector((towerData.cell.iX + 0.5f) * gridSize, (towerData.cell.iY + 0.5f) * gridSize));
			if (tower == nullptr)
				continue;
			AddActor(tower);
			for (int32 i = 1; i < towerData.grade; ++i)
				tower->ApplyUpgrade();
		}

		for (const ObstacleSaveData& obstacleData : _pendingLoadData.obstacles)
		{
			if (_map.TryOccupyCell(obstacleData.cell) == false)
				continue;
			Obstacle* obstacle = ObstacleFactory::Create(PoolManager::GetInstance().GetObstaclePool(), obstacleData.type,
				Vector((obstacleData.cell.iX + 0.5f) * gridSize, (obstacleData.cell.iY + 0.5f) * gridSize));
			if (obstacle != nullptr)
				AddActor(obstacle);
		}

		_hasPendingLoad = false;
	}
}

void GameScene::Cleanup()
{
	Super::Cleanup();
	_towerController.Reset();
	_obstacleController.Reset();
	_debugOverlay.Clear();
}

void GameScene::Update(float deltaTime)
{
	if (InputManager::GetInstance().GetButtonDown(KeyType::F2))
		_debugOverlay.Toggle();

	if (InputManager::GetInstance().GetButtonDown(KeyType::Escape) && _healthManager.IsGameOver() == false && _isVictoryOpen == false)
	{
		_isSettingsOpen = !_isSettingsOpen;
		AudioManager::GetInstance().SetBgmVolumeScale(_isSettingsOpen ? 0.3f : 1.0f);
	}

	// 설정창이 열려 있는 동안, 설정 버튼 5개(+톱니바퀴)를 제외한 모든 UI 버튼의 클릭을 막는다.
	// SetActive를 쓰지 않으므로 다른 버튼들은 계속 보이고, 클릭만 안 먹힌다.
	UIManager::GetInstance().SetInputLocked(_isSettingsOpen || _isVictoryOpen);

	if (_healthManager.IsGameOver())
	{
		_gameOverFadeTimer = std::min(_gameOverFadeTimer + deltaTime, kGameOverFadeDuration);
		// 재시작 버튼을 제외한 모든 UI(오른쪽 상점/HUD 패널 포함) 입력을 막는다.
		UIManager::GetInstance().SetInputLocked(true);

		for (Actor* actor : GetActors(RenderLayer::Bloon))
		{
			if (actor->IsActive() && actor->IsPendingKill() == false)
				actor->Update(deltaTime);
		}
		UIManager::GetInstance().Update(deltaTime);
		return;
	}

	if (_isVictoryOpen)
	{
		// 승리 팝업이 열려 있는 동안은 설정 팝업과 마찬가지로 게임 로직을 완전히 멈추고, 버튼 클릭만 받는다.
		_victoryFadeTimer = std::min(_victoryFadeTimer + deltaTime, kVictoryFadeDuration);
		UIManager::GetInstance().Update(deltaTime);
		return;
	}

	if (_isSettingsOpen)
	{
		// 설정 팝업이 열려 있는 동안은 게임 로직을 완전히 멈추고, 버튼 클릭만 받는다.
		UIManager::GetInstance().Update(deltaTime);
		return;
	}

	const float scaledDeltaTime = deltaTime * getTimeScale();

	Super::Update(scaledDeltaTime);
	_waveManager.Update(scaledDeltaTime);

	// 마지막 라운드까지 클리어하고 대기 상태로 돌아온 첫 순간에만 승리 팝업을 띄운다.
	if (_victoryPopupShown == false && _waveManager.IsWaveActive() == false &&
		_waveManager.GetDisplayRoundNumber() > _waveManager.GetTotalRoundNumber())
	{
		_victoryPopupShown = true;
		_isVictoryOpen = true;
	}

	const bool waveActive = _waveManager.IsWaveActive();
	_towerController.UpdateDrag(*this, _map, _economyManager, waveActive);
	_towerController.UpdateSelect(_map, *this);
	_obstacleController.UpdateDrag(*this, _map, _economyManager, waveActive, _waveManager.GetDisplayRoundNumber());
	_obstacleController.UpdateSelect(_map, *this);
	GetCollisionManager().Update(*this);
	updateDebugWaveTitle();

	_debugOverlay.Update(deltaTime);
}

float GameScene::getTimeScale() const
{
	constexpr float kFastTimeScale = 2.0f;
	return _speedEnabled ? kFastTimeScale : 1.0f;
}


void GameScene::AddDebugCircle(const Vector& pos, float radius, float duration)
{
	_debugOverlay.AddCircle(pos, radius, duration);
}

void GameScene::Render(Graphic& graphic)
{
	_map.RenderTiles(graphic);

	// 출발/도착 지점을 시각적으로 구분하기 위한 장식 스프라이트.
	// 타일보다는 위, 풍선(Super::Render)보다는 아래에 그려야 풍선이 항상 위에 보인다.
	// 원본 스프라이트가 커서 별도 스케일 상수로 크기를 조절한다.
	constexpr float kSpawnDecorScale = 0.5f;
	constexpr float kEndDecorScale = 0.6f;
	if (const CellInfo* startCell = _sprite->GetCell("bloonsday_pro_ball_shields"))
	{
		const Vector spawnPos = _map.GetBloonSpawnPos();
		_inGameBg->DrawSprite(graphic, spawnPos.x, spawnPos.y, *startCell, kSpawnDecorScale, 0.0f);
	}
	if (const CellInfo* endCell = _sprite->GetCell("candy_chimney_02"))
	{
		const Vector endPos = _map.GetBloonEndPos();
		_inGameBg->DrawSprite(graphic, endPos.x, endPos.y, *endCell, kEndDecorScale, 0.0f);
	}

	_debugOverlay.Render(graphic, _map,
		_towerController.IsDragging() || _obstacleController.IsDragging(),
		GetActors(RenderLayer::Bloon));

	Tower* selectedTower = _towerController.GetSelected();
	TowerSelectionInfo selection;
	if (selectedTower != nullptr)
	{
		selection.isSelected = true;
		selection.name = GetTowerDisplayName(selectedTower->GetType());
		selection.grade = selectedTower->GetGrade();
		selection.sellPrice = selectedTower->GetSellPrice();
		selection.canUpgrade = selectedTower->CanUpgrade();
		selection.upgradePrice = selectedTower->GetNextUpgradeCost();
		selection.canAfford = _economyManager.GetGold() >= selection.upgradePrice;
		selection.upgradeIconKey = selectedTower->GetNextUpgradeIconKey();
		selection.upgradeName = selectedTower->GetNextUpgradeName();
		selection.upgradeDescription = selectedTower->GetNextUpgradeDescription();
		selection.avatarKey = selectedTower->GetStat().avatarKey;
	}

	Obstacle* selectedObstacle = _obstacleController.GetSelected();
	ObstacleSelectionInfo obstacleSelection;
	if (selectedObstacle != nullptr)
	{
		obstacleSelection.isSelected = true;
		obstacleSelection.sellPrice = selectedObstacle->GetSellPrice();
	}

	const float gameOverFadeProgress = _gameOverFadeTimer / kGameOverFadeDuration;

	_ui.Render(graphic,
		_towerController.IsDragging(),
		_towerController.DraggingType(),
		_obstacleController.IsDragging(),
		InputManager::GetInstance().GetMousePos(),
		selection,
		obstacleSelection,
		_healthManager.GetHp(),
		_economyManager.GetGold(),
		_waveManager.IsWaveActive(),
		_waveManager.GetDisplayRoundNumber(),
		_waveManager.GetTotalRoundNumber(),
		_speedEnabled,
		_healthManager.IsGameOver(),
		gameOverFadeProgress);

	// 모든 타워를 그리기 전에 선택된 타워의 사거리부터 그려서, 다른 타워를 덮지 않도록 함.
	if (selectedTower != nullptr && selectedTower->GetType() != TowerType::SniperMonkey)
		selectedTower->RenderRange(graphic);

	Super::Render(graphic);

	// 게임오버 중에도 계속 움직이는 풍선 등 액터보다 위에 그려야 하므로 액터 렌더링 이후에 호출.
	_ui.RenderGameOverPopup(graphic, _healthManager.IsGameOver(), gameOverFadeProgress, _waveManager.GetDisplayRoundNumber());

	// 승리 팝업도 게임오버 팝업과 같은 레이어(액터 렌더링 이후)에 그린다.
	const float victoryFadeProgress = _victoryFadeTimer / kVictoryFadeDuration;
	_ui.RenderVictoryPopup(graphic, _isVictoryOpen, victoryFadeProgress);

	// 배치된 타워 등 액터보다 위에 그려야 하므로 액터 렌더링 이후에 호출.
	// 게임오버/설정 팝업이 떠 있는 동안은 툴팁을 보이지 않게 한다.
	if (_isSettingsOpen == false && _healthManager.IsGameOver() == false)
		_ui.RenderTooltips(graphic, selection);

	// 액터/버튼까지 전부 그려진 뒤 맨 마지막에 덧그려야 설정 팝업이 항상 최상단에 보인다.
	_ui.RenderModalOverlay(graphic, _isSettingsOpen);
}

void GameScene::CreateUI()
{
	_ui.Init(
		[this]() {onStartButtonClick(); },
		[this]() { _towerController.TryStartDrag(TowerType::DartMonkey, _economyManager); },
		[this]() { _towerController.TryStartDrag(TowerType::TackShooter, _economyManager); },
		[this]() { _towerController.TryStartDrag(TowerType::SniperMonkey, _economyManager); },
		[this]() { _towerController.TryStartDrag(TowerType::BombTower, _economyManager); },
		[this]() { _obstacleController.TryStartDrag(*this, _waveManager.GetDisplayRoundNumber(), _economyManager); },
		[this]() { _waveManager.SetNextRound(_waveManager.GetNextRoundNumber() + 1); },
		[this]() { _waveManager.SetNextRound(_waveManager.GetNextRoundNumber() - 1); },
		[this]() { _economyManager.Add(1000); },
		[this]() { _healthManager.Add(10); },
		[this]() { _economyManager.Add(-1000); },
		[this]()
		{
			// 10 밑으로는 못 내려가게 막는다.
			_healthManager.Add(-std::clamp(_healthManager.GetHp() - 10, 0, 10));
		},
		[this]() { _towerController.SellSelected(_map, _economyManager); },
		[this]() { _towerController.UpgradeSelected(_economyManager); },
		[this]() { _obstacleController.SellSelected(_map, _economyManager); },
		[this]() { Restart(); },
		[this]()
		{
			if (_healthManager.IsGameOver()) return; // 게임오버 중에는 설정창을 열 수 없다.
			_isSettingsOpen = !_isSettingsOpen;
			AudioManager::GetInstance().SetBgmVolumeScale(_isSettingsOpen ? 0.3f : 1.0f);
		},
		[this]() { _isSettingsOpen = false; AudioManager::GetInstance().SetBgmVolumeScale(1.0f); },
		[this]() { Restart(); },
		[this]()
		{
			_isSettingsOpen = false;
			AudioManager::GetInstance().SetBgmVolumeScale(1.0f);
			UIManager::GetInstance().SetInputLocked(false); // 씬 전환 전에 입력 잠금을 풀어야 로비 UI가 눌린다.
			SceneManager::GetInstance().ChangeScene(SceneType::Lobby);
		},
		[this](bool enabled) { _waveManager.SetAutoPlay(enabled); },
		[this]() { _isVictoryOpen = false; });
	updateDebugWaveTitle();
}


void GameScene::Restart()
{
	Graphic* graphic = _graphicRef;
	SaveManager::DeleteFile(kSaveFilePath); // 재시작(게임오버/리플레이)은 새 판이므로 자동저장도 같이 초기화
	Cleanup();
	if (graphic != nullptr)
		Init(*graphic);
}

SaveData GameScene::BuildSaveData() const
{
	SaveData data;
	data.gold = _economyManager.GetGold();
	data.hp = _healthManager.GetHp();
	data.nextRound = _waveManager.GetNextRoundNumber();
	data.autoPlay = _waveManager.GetAutoPlay();
	data.speedEnabled = _speedEnabled;
	data.startCell = _map.GetStartCell();
	data.endCell = _map.GetEndCell();

	const int32 gridSize = _map.GetGridSize();
	for (Actor* actor : GetActors(RenderLayer::Tower))
	{
		const Tower* tower = static_cast<const Tower*>(actor);
		data.towers.push_back({ tower->GetType(), tower->GetGrade(), Cell::ConvertToCell(tower->GetPos(), gridSize) });
	}

	for (Actor* actor : GetActors(RenderLayer::Obstacle))
	{
		const Obstacle* obstacle = static_cast<const Obstacle*>(actor);
		data.obstacles.push_back({ obstacle->GetType(), Cell::ConvertToCell(obstacle->GetPos(), gridSize) });
	}

	return data;
}

void GameScene::SaveToFile(const wstring& path) const
{
	if (CanSave() == false)
		return;
	SaveManager::WriteToFile(BuildSaveData(), path);
}

void GameScene::LoadFromFile(const wstring& path)
{
	SaveData data;
	if (SaveManager::ReadFromFile(data, path) == false)
		return;
	_pendingLoadData = data;
	_hasPendingLoad = true;
	Restart();
}

bool GameScene::PrepareLoad(const wstring& path)
{
	SaveData data;
	if (SaveManager::ReadFromFile(data, path) == false)
		return false;
	_pendingLoadData = data;
	_hasPendingLoad = true;
	return true;
}

void GameScene::onStartButtonClick()
{
	if (_waveManager.IsWaveActive() == false)
	{
		if (_map.HasPath() == false)
			return; // 도착 지점에 갈 경로가 없으면 웨이브를 시작하지 않는다.

		_waveManager.StartNextWave();
		return;
	}
	_speedEnabled = !_speedEnabled;
}

Projectile* GameScene::SpawnProjectile(const Vector& pos,const Vector& dir, float damage, const string& spriteKey, float speed, float maxDistance, float splashRadius, int32 pierceCount)
{
	Projectile* projectile = ProjectileFactory::Create(PoolManager::GetInstance().GetProjectilePool(), pos, dir, damage, spriteKey, speed, maxDistance, splashRadius, pierceCount);
	if (projectile != nullptr)
		AddActor(projectile);

	return projectile;
}

void GameScene::updateDebugWaveTitle()
{
	const int32 currentRound = _waveManager.GetCurrentRoundNumber();
	const int32 nextRound = _waveManager.GetNextRoundNumber();

	if (currentRound == _lastTitleCurrentRound && nextRound == _lastTitleNextRound)
		return;

	_lastTitleCurrentRound = currentRound;
	_lastTitleNextRound = nextRound;

	wchar_t title[64];
	if (currentRound > 0)
		swprintf_s(title, L"TowerDefense - 현재 웨이브: %d / 다음 시작 웨이브: %d", currentRound, nextRound);
	else
		swprintf_s(title, L"TowerDefense - 다음 시작 웨이브: %d", nextRound);

	SetWindowText(Game::GetInstance().GetHwnd(), title);
}

