#include "pch.h"
#include "GameScene.h"
#include "InputManager.h"
#include "UIManager.h"
#include "Tower.h"
#include "TowerFactory.h"
#include "Obstacle.h"
#include "ObstacleFactory.h"
#include "PoolManager.h"
#include "Game.h"

void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);
	_graphicRef = &graphic;

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

	PoolManager::GetInstance().Init(200, 200, 50, 50); // obstacleSize=50: 임시값
	_waveManager.Init(&PoolManager::GetInstance().GetBloonPool(), _bloonSpawnPos, &_path, this);
	_healthManager.Init(100); // 초기 체력: 임시값 — 밸런스 확정되면 조정
	_economyManager.Init(10000); // 초기 골드: 임시값 — 밸런스 확정되면 조정

	GetCollisionManager().RegisterLayer(RenderLayer::Bloon, RenderLayer::Projectile);

	_speedEnabled = false;

}

void GameScene::Cleanup()
{
	Super::Cleanup();
	_selectedTower = nullptr;
}

void GameScene::Update(float deltaTime)
{
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

	const float scaledDeltaTime = deltaTime * getTimeScale();

	Super::Update(scaledDeltaTime);
	_waveManager.Update(scaledDeltaTime);

	updateTowerDrag();
	updateObstacleDrag();
	updateTowerSelect();
	updateObstacleSelect();
	GetCollisionManager().Update(*this);
	updateDebugWaveTitle();

	for (DebugCircle& circle : _debugCircles)
		circle.remaining -= deltaTime;

	std::erase_if(_debugCircles, [](const DebugCircle& circle)
		{
			return circle.remaining <= 0.f;
		});
}

float GameScene::getTimeScale() const
{
	constexpr float kFastTimeScale = 2.0f;
	return _speedEnabled ? kFastTimeScale : 1.0f;
}


void GameScene::AddDebugCircle(const Vector& pos, float radius, float duration)
{
	_debugCircles.push_back({ pos,radius,duration });
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
	//const CellInfo* tackLogoCell = _sprite->GetCell("bomb_tower_01");
	//if (tackLogoCell)
	//{
	//	_inGameBg->DrawSprite(graphic, 400.0f, 400.0f, *tackLogoCell, 1.0f);
	//}

	renderGrid(graphic);
	renderPathDebug(graphic);
	renderStartEndDebug(graphic);
	renderDebugCircles(graphic);

	TowerSelectionInfo selection;
	if (_selectedTower != nullptr)
	{
		selection.isSelected = true;
		selection.grade = _selectedTower->GetGrade();
		selection.sellPrice = _selectedTower->GetSellPrice();
		selection.canUpgrade = _selectedTower->CanUpgrade();
		selection.upgradePrice = _selectedTower->GetNextUpgradeCost();
	}

	ObstacleSelectionInfo obstacleSelection;
	if (_selectedObstacle != nullptr)
	{
		obstacleSelection.isSelected = true;
		obstacleSelection.sellPrice = _selectedObstacle->GetSellPrice();
	}

	_ui.Render(graphic,
		_isDraggingTower,
		_draggingTowerType,
		_isDraggingObstacle,
		InputManager::GetInstance().GetMousePos(),
		selection,
		obstacleSelection,
		_healthManager.GetHp(),
		_economyManager.GetGold(),
		_waveManager.IsWaveActive(),
		_speedEnabled,
		_healthManager.IsGameOver());

	Super::Render(graphic);
}

void GameScene::CreateUI()
{
	_ui.Init(
		[this]() {onStartButtonClick(); },
		[this]() { tryStartTowerDrag(TowerType::DartMonkey); },
		[this]() { tryStartTowerDrag(TowerType::TackShooter); },
		[this]() { tryStartTowerDrag(TowerType::SniperMonkey); },
		[this]() { tryStartTowerDrag(TowerType::BombTower); },
		[this]() { tryStartObstacleDrag(); },
		[this]() { _waveManager.SetNextRound(_waveManager.GetNextRoundNumber() + 1); },
		[this]() { _waveManager.SetNextRound(_waveManager.GetNextRoundNumber() - 1); },
		[this]() { sellSelectedTower(); },
		[this]() { upgradeSelectedTower(); },
		[this]() { sellSelectedObstacle(); },
		[this]() { Restart(); });
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
		_waveManager.StartNextWave();
		return;
	}
	_speedEnabled = !_speedEnabled;
}

Projectile* GameScene::SpawnProjectile(const Vector& pos,const Vector& dir, float damage, const string& spriteKey, float speed, float splashRadius, int32 pierceCount)
{
	Projectile* projectile = ProjectileFactory::Create(PoolManager::GetInstance().GetProjectilePool(), pos, dir, damage, spriteKey, speed, splashRadius, pierceCount);
	if (projectile != nullptr)
		AddActor(projectile);

	return projectile;
}

bool GameScene::isCellOccupied(const Cell& cell) const
{
	const int32 gridSize = _grid.GetGridSize();
	auto hasActorAt = [&](RenderLayer layer)
	{
		for (Actor* actor : GetActors(layer))
		{
			if (actor->IsPendingKill())
				continue;
			const Cell actorCell = Cell::ConvertToCEll(actor->GetPos(), gridSize);
			if (actorCell.iX == cell.iX && actorCell.iY == cell.iY)
				return true;
		}
		return false;
	};
	return hasActorAt(RenderLayer::Tower) || hasActorAt(RenderLayer::Obstacle);
}

// 설치 가능한 칸인지 찾아서 실제로 막고 골드를 쓰고 만들어주는 뼈대.
// 실패하면(범위 밖/중복/경로 막힘/골드 부족) 아무 부작용 없이 false.
bool GameScene::tryPlaceOnGrid(int32 price, const function<Actor* (const Vector&)>& createFn)
{
	const Vector mousePos = InputManager::GetInstance().GetMousePos();
	if (mousePos.x < 0.f || mousePos.x >= GameAreaWidth
		|| mousePos.y < 0.f || mousePos.y >= GameAreaHeight)
		return false; // 게임 영역(그리드) 밖에서 손을 떼면 설치하지 않는다.

	const int32 gridSize = _grid.GetGridSize();
	const Cell targetCell = Cell::ConvertToCEll(mousePos, gridSize);
	const Cell startCell = _tileMap.GetStartPoint();
	const Cell endCell = _tileMap.GetEndPoint();

	if ((targetCell.iX == startCell.iX && targetCell.iY == startCell.iY)
		|| (targetCell.iX == endCell.iX && targetCell.iY == endCell.iY))
		return false;

	if (isCellOccupied(targetCell))
		return false; // 이미 타워나 장애물이 있는 셀에는 중복 설치 금지

	_tileMap.SetTile(targetCell.iX, targetCell.iY, TileType::Obstacle);
	vector<Vector> newPath = PathFinder::FindPath(_tileMap, startCell,
		endCell, GRID_COUNT_X, GRID_COUNT_Y, gridSize);
	if (newPath.empty() || _economyManager.TrySpend(price) == false)
	{
		_tileMap.SetTile(targetCell.iX, targetCell.iY, TileType::Path);
		return false;
	}

	_path = std::move(newPath);

	const Vector spawnPos((targetCell.iX + 0.5f) * gridSize, (targetCell.iY + 0.5f) * gridSize);
	if (Actor* actor = createFn(spawnPos))
		AddActor(actor);
	else
		_economyManager.Add(price); // 생성 실패 시 차감했던 골드 환불
	return true;
}

// 클릭한 칸에 있는 액터를 찾아준다 (선택용).
Actor* GameScene::findActorAt(const Vector& pos, RenderLayer layer) const
{
	const int32 gridSize = _grid.GetGridSize();
	const Cell clickCell = Cell::ConvertToCEll(pos, gridSize);
	for (Actor* actor : GetActors(layer))
	{
		if (actor->IsPendingKill())
			continue;
		const Cell cell = Cell::ConvertToCEll(actor->GetPos(), gridSize);
		if (cell.iX == clickCell.iX && cell.iY == clickCell.iY)
			return actor;
	}
	return nullptr;
}

// 판매(타일 되돌리고 경로 재계산)만 공통 처리. 골드 환불/액터 삭제는 호출부 책임.
void GameScene::clearTileAndRepath(const Vector& pos)
{
	const int32 gridSize = _grid.GetGridSize();
	const Cell cell = Cell::ConvertToCEll(pos, gridSize);
	_tileMap.SetTile(cell.iX, cell.iY, TileType::Path);

	const Cell startCell = _tileMap.GetStartPoint();
	const Cell endCell = _tileMap.GetEndPoint();
	_path = PathFinder::FindPath(_tileMap, startCell, endCell, GRID_COUNT_X, GRID_COUNT_Y, gridSize);
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

	const TowerType type = _draggingTowerType;
	_isDraggingTower = false;

	tryPlaceOnGrid(GetTowerStat(type).basePrice, [&](const Vector& pos)
	{
		return static_cast<Actor*>(TowerFactory::Create(PoolManager::GetInstance().GetTowerPool(), type, pos));
	});
}

void GameScene::tryStartObstacleDrag()
{
	if (_waveManager.IsWaveActive())
		return;

	if (_economyManager.GetGold() < GetObstacleStat(ObstacleType::BananaFarmTree).basePrice)
		return;

	_isDraggingObstacle = true;
}

void GameScene::updateObstacleDrag()
{
	if (_isDraggingObstacle == false)
		return;

	if (InputManager::GetInstance().GetButtonUp(KeyType::LeftMouse) == false)
		return;

	_isDraggingObstacle = false;

	tryPlaceOnGrid(GetObstacleStat(ObstacleType::BananaFarmTree).basePrice, [&](const Vector& pos)
	{
		return static_cast<Actor*>(ObstacleFactory::Create(PoolManager::GetInstance().GetObstaclePool(), ObstacleType::BananaFarmTree, pos));
	});
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

	_selectedTower = static_cast<Tower*>(findActorAt(mousePos, RenderLayer::Tower));
}

void GameScene::updateObstacleSelect()
{
	if (_isDraggingObstacle)
		return;

	if (InputManager::GetInstance().GetButtonDown(KeyType::LeftMouse) == false)
		return;

	const Vector mousePos = InputManager::GetInstance().GetMousePos();
	if (mousePos.x < 0.f || mousePos.x >= GameAreaWidth
		|| mousePos.y < 0.f || mousePos.y >= GameAreaHeight)
		return;

	_selectedObstacle = static_cast<Obstacle*>(findActorAt(mousePos, RenderLayer::Obstacle));
}

void GameScene::sellSelectedTower()
{
	if (_selectedTower == nullptr)
		return;

	_economyManager.Add(_selectedTower->GetSellPrice());
	clearTileAndRepath(_selectedTower->GetPos());

	_selectedTower->SetPendingKill();
	_selectedTower = nullptr;
}

void GameScene::sellSelectedObstacle()
{
	if (_selectedObstacle == nullptr)
		return;

	_economyManager.Add(_selectedObstacle->GetSellPrice());
	clearTileAndRepath(_selectedObstacle->GetPos());

	_selectedObstacle->SetPendingKill();
	_selectedObstacle = nullptr;
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

void GameScene::renderDebugCircles(Graphic& graphic)
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 0.6f));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	for (const DebugCircle& circle : _debugCircles)
		renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(circle.pos.x, circle.pos.y), circle.radius, circle.radius), brush, 2.f);
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
