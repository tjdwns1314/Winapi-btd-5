#include "pch.h"
#include "GameScene.h"
#include "InputManager.h"
#include "Tower.h"
#include "TowerFactory.h"
#include "PoolManager.h"
#include "Game.h"

void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);

	ResourceManager& res = ResourceManager::GetInstance();

	_monkeyLaneBg = &res.GetImage(L"Resource\\Sprite\\monkey_lane.png");
	_monkeyLaneSprite = &res.GetAtlas(L"Resource\\Sprite\\monkey_lane.xml");

	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");

	_tile1Img = &res.GetImage(L"Resource\\Tile\\Tile1.png");
	_tile2Img = &res.GetImage(L"Resource\\Tile\\Tile2.png");

	_hudImg = &res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");

	_blueImg = &res.GetImage(L"Resource\\Blue.png");

	_grid.Init(GRID_COUNT_X, GRID_COUNT_Y, BLOCK_SIZE);
	_tileMap.Init(GRID_COUNT_X, GRID_COUNT_Y); // 기본값 TileType::Path로 전체 채움
	_tileMap.GenerateRandomStartEndPoint();

	const Cell startCell = _tileMap.GetStartPoint();
	const Cell endCell = _tileMap.GetEndPoint();
	const int32 gridSize = _grid.GetGridSize();
	_path = PathFinder::FindPath(_tileMap, startCell, endCell, GRID_COUNT_X, GRID_COUNT_Y, gridSize);

	_bloonSpawnPos = Vector(
		(startCell.iX + 0.5f) * gridSize,
		(startCell.iY + 0.5f) * gridSize);

	PoolManager::GetInstance().Init(200, 200, 50);
	_waveManager.Init(&PoolManager::GetInstance().GetBloonPool(), _bloonSpawnPos, &_path, this);
	_healthManager.Init(100); // 초기 체력: 임시값 — 밸런스 확정되면 조정
	_economyManager.Init(10000); // 초기 골드: 임시값 — 밸런스 확정되면 조정

	GetCollisionManager().RegisterLayer(RenderLayer::Bloon, RenderLayer::Projectile);
}

void GameScene::Cleanup()
{
	Super::Cleanup();
}

void GameScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
	_waveManager.Update(deltaTime);
	updateTowerDrag();
	updateTowerSelect();
	GetCollisionManager().Update(*this);
	updateDebugWaveTitle();
}

void GameScene::Render(Graphic& graphic)
{
	renderTileMap(graphic);

	// [임시 테스트] Blue.png 단일 이미지 확인용 - 확인 끝나면 제거
	//_blueImg->Draw(graphic, 400.0f, 400.0f, 1.0f);

	const CellInfo* thumbBoxCell = _hudSprite->GetCell("side_hud_bg_01");
	if (thumbBoxCell)
	{
		_hudImg->DrawSprite(graphic, 1575.0f, 135.0f, *thumbBoxCell, 1.0f);
	}

	// [임시 테스트] tack_shooter_tack_logo 확인용 - 확인 끝나면 제거
	const CellInfo* tackLogoCell = _sprite->GetCell("bomb_tower_01");
	if (tackLogoCell)
	{
		_inGameBg->DrawSprite(graphic, 400.0f, 400.0f, *tackLogoCell, 1.0f);
	}

	renderGrid(graphic);
	renderPathDebug(graphic);
	renderStartEndDebug(graphic);

	TowerSelectionInfo selection;
	if (_selectedTower != nullptr)
	{
		selection.isSelected = true;
		selection.sellPrice = _selectedTower->GetSellPrice();
		selection.canUpgrade = _selectedTower->CanUpgrade();
		selection.upgradePrice = _selectedTower->GetNextUpgradeCost();
	}
	_ui.Render(graphic,
		_isDraggingTower,
		_draggingTowerType,
		InputManager::GetInstance().GetMousePos(),
		selection,
		_healthManager.GetHp(),
		_economyManager.GetGold());

	Super::Render(graphic);
}

void GameScene::CreateUI()
{
	_ui.Init(
		[this]() { _waveManager.StartNextWave(); },
		[this]() { tryStartTowerDrag(TowerType::DartMonkey); },
		[this]() { tryStartTowerDrag(TowerType::TackShooter); },
		[this]() { tryStartTowerDrag(TowerType::SniperMonkey); },
		[this]() { tryStartTowerDrag(TowerType::BombTower); },
		[this]() { _waveManager.SetNextRound(_waveManager.GetNextRoundNumber() + 1); },
		[this]() { _waveManager.SetNextRound(_waveManager.GetNextRoundNumber() - 1); },
		[this]() { sellSelectedTower(); },
		[this]() { upgradeSelectedTower(); });

	updateDebugWaveTitle();
}

Projectile* GameScene::SpawnProjectile(const Vector& pos,
	const Vector& dir, float damage, const string& spriteKey, float speed)
{
	Projectile* projectile = ProjectileFactory::Create(PoolManager::GetInstance().GetProjectilePool(), pos, dir, damage, spriteKey, speed);
	if (projectile != nullptr)
		AddActor(projectile);

	return projectile;
}

void GameScene::tryStartTowerDrag(TowerType type)
{
	if (_waveManager.IsWaveActive())
		return;

	if (_economyManager.GetGold() < GetTowerStat(type).basePrice)
		return; // 골드가 부족하면 드래그를 시작하지 않는다.

	_isDraggingTower = true;
	_draggingTowerType = type;
}

void GameScene::updateTowerDrag()
{
	if (_isDraggingTower == false)
		return;

	if (InputManager::GetInstance().GetButtonUp(KeyType::LeftMouse) == false)
		return;

	const TowerType towerType = _draggingTowerType;
	_isDraggingTower = false;

	const Vector mousePos = InputManager::GetInstance().GetMousePos();
	if (mousePos.x < 0.f || mousePos.x >= GameAreaWidth
		|| mousePos.y < 0.f || mousePos.y >= GameAreaHeight)
		return; // 게임 영역(그리드) 밖에서 손을 떼면 설치하지 않는다.

	const int32 gridSize = _grid.GetGridSize();
	const Cell targetCell = Cell::ConvertToCEll(mousePos, gridSize);

	const Cell startCell = _tileMap.GetStartPoint();
	const Cell endCell = _tileMap.GetEndPoint();

	if ((targetCell.iX == startCell.iX && targetCell.iY == startCell.iY)
		|| (targetCell.iX == endCell.iX && targetCell.iY == endCell.iY))
		return;

	for (Actor* actor : GetActors(RenderLayer::Tower))
	{
		if (actor->IsPendingKill())
			continue;

		const Cell cell = Cell::ConvertToCEll(actor->GetPos(), gridSize);
		if (cell.iX == targetCell.iX && cell.iY == targetCell.iY)
			return; // 이미 타워가 있는 셀에는 중복 설치 금지
	}

	_tileMap.SetTile(targetCell.iX, targetCell.iY, TileType::Obstacle);
	vector<Vector> newPath = PathFinder::FindPath(_tileMap, startCell,
		endCell, GRID_COUNT_X, GRID_COUNT_Y, gridSize);
	if (newPath.empty())
	{
		_tileMap.SetTile(targetCell.iX, targetCell.iY, TileType::Path);
		return;
	}

	const int32 price = GetTowerStat(towerType).basePrice;
	if (_economyManager.TrySpend(price) == false)
	{
		_tileMap.SetTile(targetCell.iX, targetCell.iY, TileType::Path);
		return; // 골드 부족 시 설치 취소
	}

	_path = std::move(newPath);

	Tower* tower = TowerFactory::Create(PoolManager::GetInstance().GetTowerPool(), towerType,
		Vector((targetCell.iX + 0.5f) * gridSize, (targetCell.iY + 0.5f) * gridSize));
	if (tower != nullptr)
	{
		AddActor(tower);
	}
	else
	{
		_economyManager.Add(price); // 생성 실패 시 차감했던 골드 환불
	}
}

void GameScene::updateTowerSelect()
{
	if (_isDraggingTower)
		return;

	if (InputManager::GetInstance().GetButtonDown(KeyType::LeftMouse) == false)
		return;

	const Vector mousePos = InputManager::GetInstance().GetMousePos();
	if (mousePos.x < 0.f || mousePos.x >= GameAreaWidth
		|| mousePos.y < 0.f || mousePos.y >= GameAreaHeight)
		return; // 게임 영역 밖(우측 HUD 등) 클릭은 선택에 영향을 주지 않는다.

	const int32 gridSize = _grid.GetGridSize();
	const Cell clickCell = Cell::ConvertToCEll(mousePos, gridSize);

	_selectedTower = nullptr;
	for (Actor* actor : GetActors(RenderLayer::Tower))
	{
		if (actor->IsPendingKill())
			continue;

		const Cell cell = Cell::ConvertToCEll(actor->GetPos(), gridSize);
		if (cell.iX == clickCell.iX && cell.iY == clickCell.iY)
		{
			_selectedTower = static_cast<Tower*>(actor);
			break;
		}
	}
}

void GameScene::sellSelectedTower()
{
	if (_selectedTower == nullptr)
		return;

	_economyManager.Add(_selectedTower->GetSellPrice());

	const int32 gridSize = _grid.GetGridSize();
	const Cell cell = Cell::ConvertToCEll(_selectedTower->GetPos(), gridSize);
	_tileMap.SetTile(cell.iX, cell.iY, TileType::Path);

	const Cell startCell = _tileMap.GetStartPoint();
	const Cell endCell = _tileMap.GetEndPoint();
	_path = PathFinder::FindPath(_tileMap, startCell, endCell, GRID_COUNT_X, GRID_COUNT_Y, gridSize);

	_selectedTower->SetPendingKill();
	_selectedTower = nullptr;
}

void GameScene::upgradeSelectedTower()
{
	if (_selectedTower == nullptr || _selectedTower->CanUpgrade() == false)
		return;

	const int32 cost = _selectedTower->GetNextUpgradeCost();
	if (_economyManager.TrySpend(cost) == false)
		return; // 골드 부족

	_selectedTower->ApplyUpgrade();
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

void GameScene::renderTileMap(Graphic& graphic)
{
	const D2D1_SIZE_F size1 = _tile1Img->GetSize();
	const float scale1 = static_cast<float>(BLOCK_SIZE) / size1.width;

	const D2D1_SIZE_F size2 = _tile2Img->GetSize();
	const float scale2 = static_cast<float>(BLOCK_SIZE) / size2.width;

	for (int32 y = 0; y < GRID_COUNT_Y; ++y)
	{
		for (int32 x = 0; x < GRID_COUNT_X; ++x)
		{
			const TileType tile = _tileMap.GetTile(x, y);
			if (tile != TileType::Path && tile != TileType::Obstacle)
				continue;

			const float cx = (x + 0.5f) * BLOCK_SIZE;
			const float cy = (y + 0.5f) * BLOCK_SIZE;
			if (tile == TileType::Path)
				_tile1Img->Draw(graphic, cx, cy, scale1);
			else
				_tile2Img->Draw(graphic, cx, cy, scale2);
		}
	}
}

void GameScene::renderGrid(Graphic& graphic)
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Gray, 0.5f));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	const int32 gridSize = _grid.GetGridSize();
	const float width = static_cast<float>(GRID_COUNT_X * gridSize);
	const float height = static_cast<float>(GRID_COUNT_Y * gridSize);

	for (int32 x = 0; x <= GRID_COUNT_X; ++x)
	{
		const float px = static_cast<float>(x * gridSize);
		renderTarget->DrawLine(D2D1::Point2F(px, 0.f), D2D1::Point2F(px, height), brush);
	}

	for (int32 y = 0; y <= GRID_COUNT_Y; ++y)
	{
		const float py = static_cast<float>(y * gridSize);
		renderTarget->DrawLine(D2D1::Point2F(0.f, py), D2D1::Point2F(width, py), brush);
	}
}

void GameScene::renderPathDebug(Graphic& graphic)
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Blue));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	const float radius = static_cast<float>(_grid.GetGridSize()) * 0.15f;

	for (const Vector& point : _path)
	{
		renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(point.x, point.y), radius, radius), brush);
	}
}

void GameScene::renderStartEndDebug(Graphic& graphic)
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	if (renderTarget == nullptr)
		return;

	const int32 gridSize = _grid.GetGridSize();
	const float radius = static_cast<float>(gridSize) * 0.3f;

	auto drawCellMarker = [&](Cell cell, const D2D1::ColorF& color)
	{
		ID2D1SolidColorBrush* brush = graphic.GetBrush(color);
		if (brush == nullptr)
			return;

		const float cx = (cell.iX + 0.5f) * gridSize;
		const float cy = (cell.iY + 0.5f) * gridSize;
		renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), radius, radius), brush);
	};

	drawCellMarker(_tileMap.GetStartPoint(), D2D1::ColorF(D2D1::ColorF::Green));
	drawCellMarker(_tileMap.GetEndPoint(), D2D1::ColorF(D2D1::ColorF::Red));
}
