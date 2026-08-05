#include "pch.h"
#include "GameScene.h"
#include "UIManager.h"
#include "Tower.h"

void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);

	ResourceManager& res = ResourceManager::GetInstance();

	_monkeyLaneBg = &res.GetImage(L"Resource\\monkey_lane.png");
	_monkeyLaneSprite = &res.GetAtlas(L"Resource\\monkey_lane.xml");

	_inGameBg = &res.GetImage(L"Resource\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\InGame.xml");

	_tile1Img = &res.GetImage(L"Resource\\Tile1.png");

	_hudImg = &res.GetImage(L"Resource\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\in_game_hud.xml");

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

	_startButton.SetPos(Vector(1575.0f, 450.0f));
	_startButton.SetSize(Vector(128.0f, 129.0f));
	_startButton.SetActive(true);
	_startButton.SetOnClick([this]()
		{
			_waveManager.StartWave(0);
			_startButton.SetActive(false);
		});

	_bloonPool.Init(200);
	_projectilePool.Init(200);
	_waveManager.Init(&_bloonPool, _bloonSpawnPos, &_path, this);

	Tower* tower = new Tower();
	tower->SetPos(Vector(2.5f * gridSize, 2.5f * gridSize));
	tower->Init();
	AddActor(tower);

	UIManager::GetInstance().Register(&_startButton);



}

Projectile* GameScene::SpawnProjectile(const Vector& pos, const Vector& dir, float damage)
{
	Projectile* projectile = ProjectileFactory::Create(_projectilePool, pos, dir, damage);
	if (projectile != nullptr)
		AddActor(projectile);
	return projectile;
}

void GameScene::Render(Graphic& graphic)
{
	renderTileMap(graphic);

	const CellInfo* thumbBoxCell = _hudSprite->GetCell("side_hud_bg_01");
	if (thumbBoxCell)
	{
		_hudImg->DrawSprite(graphic, 1575.0f, 135.0f, *thumbBoxCell,1.0f);
	}

	renderGrid(graphic);
	renderPathDebug(graphic);
	renderStartEndDebug(graphic);
	renderStartButton(graphic);

	Super::Render(graphic);
}

void GameScene::renderStartButton(Graphic& graphic)
{
	const CellInfo* playCell = _hudSprite->GetCell("play_icon");
	if (playCell == nullptr)
		return;

	const  Vector pos = _startButton.GetPos();
	_hudImg->DrawSprite(graphic, pos.x, pos.y, *playCell, 1.0f, 0.0f);
}


void GameScene::renderTileMap(Graphic& graphic)
{
	const D2D1_SIZE_F size = _tile1Img->GetSize();
	const float scale = static_cast<float>(BLOCK_SIZE) / size.width;

	for (int32 y = 0; y < GRID_COUNT_Y; ++y)
	{
		for (int32 x = 0; x < GRID_COUNT_X; ++x)
		{
			if (_tileMap.GetTile(x, y) != TileType::Path)
				continue; // Buildable/Obstacle 렌더링은 이후 추가

			const float cx = (x + 0.5f) * BLOCK_SIZE;
			const float cy = (y + 0.5f) * BLOCK_SIZE;
			_tile1Img->Draw(graphic, cx, cy, scale);
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

void GameScene::Cleanup()
{
	UIManager::GetInstance().Clear();
	Super::Cleanup();
}

void GameScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
	_waveManager.Update(deltaTime);
	UIManager::GetInstance().Update(deltaTime);
}
