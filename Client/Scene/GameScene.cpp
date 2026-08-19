#include "pch.h"
#include "GameScene.h"
#include "InputManager.h"
#include "UIManager.h"
#include "Tower.h"
#include "Obstacle.h"
#include "PoolManager.h"
#include "Game.h"
#include "AudioManager.h"
#include "AudioManager.h"

void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);
	_graphicRef = &graphic;

	ResourceManager& res = ResourceManager::GetInstance();

	_monkeyLaneBg = &res.GetImage(L"Resource\\Sprite\\monkey_lane.png");
	_monkeyLaneSprite = &res.GetAtlas(L"Resource\\Sprite\\monkey_lane.xml");

	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");

	_map.SetTileImages(&res.GetImage(L"Resource\\Tile\\Tile1_pipo.png"), &res.GetImage(L"Resource\\Tile\\Tile2_pipo.png"));
	_map.Init();

	PoolManager::GetInstance().Init(250, 200, 50, 50, 250); // obstacleSize=50, effectSize=250: 임시값
	_waveManager.Init(&PoolManager::GetInstance().GetBloonPool(), _map.GetBloonSpawnPos(), _map.GetPathPtr(), this,
		[this](int32 bonusGold) { _economyManager.Add(bonusGold); });
	_healthManager.Init(100); // 초기 체력: 임시값 — 밸런스 확정되면 조정
	_economyManager.Init(10000); // 초기 골드: 임시값 — 밸런스 확정되면 조정

	GetCollisionManager().RegisterLayer(RenderLayer::Bloon, RenderLayer::Projectile);

	_speedEnabled = false;

	AudioManager::GetInstance().PlayBgm(L"jazz");
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

	if (InputManager::GetInstance().GetButtonDown(KeyType::Escape) && _healthManager.IsGameOver() == false)
	{
		_isSettingsOpen = !_isSettingsOpen;
		AudioManager::GetInstance().SetBgmVolumeScale(_isSettingsOpen ? 0.3f : 1.0f);
	}

	// 설정창이 열려 있는 동안, 설정 버튼 5개(+톱니바퀴)를 제외한 모든 UI 버튼의 클릭을 막는다.
	// SetActive를 쓰지 않으므로 다른 버튼들은 계속 보이고, 클릭만 안 먹힌다.
	UIManager::GetInstance().SetInputLocked(_isSettingsOpen);

	if (_healthManager.IsGameOver())
	{
		for (Actor* actor : GetActors(RenderLayer::Bloon))
		{
			if (actor->IsActive() && actor->IsPendingKill() == false)
				actor->Update(deltaTime);
		}
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

	const bool waveActive = _waveManager.IsWaveActive();
	_towerController.UpdateDrag(*this, _map, _economyManager, waveActive);
	_towerController.UpdateSelect(_map, *this);
	_obstacleController.UpdateDrag(*this, _map, _economyManager, waveActive);
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
		_healthManager.IsGameOver());

	// 모든 타워를 그리기 전에 선택된 타워의 사거리부터 그려서, 다른 타워를 덮지 않도록 함.
	if (selectedTower != nullptr && selectedTower->GetType() != TowerType::SniperMonkey)
		selectedTower->RenderRange(graphic);

	Super::Render(graphic);

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
		[this]() { _obstacleController.TryStartDrag(_economyManager); },
		[this]() { _waveManager.SetNextRound(_waveManager.GetNextRoundNumber() + 1); },
		[this]() { _waveManager.SetNextRound(_waveManager.GetNextRoundNumber() - 1); },
		[this]() { _towerController.SellSelected(_map, _economyManager); },
		[this]() { _towerController.UpgradeSelected(_economyManager); },
		[this]() { _obstacleController.SellSelected(_map, _economyManager); },
		[this]() { Restart(); },
		[this]() { _isSettingsOpen = !_isSettingsOpen; AudioManager::GetInstance().SetBgmVolumeScale(_isSettingsOpen ? 0.3f : 1.0f); },
		[this]() { _isSettingsOpen = false; AudioManager::GetInstance().SetBgmVolumeScale(1.0f); });
	updateDebugWaveTitle();
}


void GameScene::Restart()
{
	Graphic* graphic = _graphicRef;
	Cleanup();
	if (graphic != nullptr)
		Init(*graphic);
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

