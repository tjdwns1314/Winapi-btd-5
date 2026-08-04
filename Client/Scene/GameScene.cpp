#include "pch.h"
#include "GameScene.h"
#include "Bloon.h"


void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);

	ResourceManager& res = ResourceManager::GetInstance();

	_monkeyLaneBg = &res.GetImage(L"Resource\\monkey_lane.png");
	_monkeyLaneSprite = &res.GetAtlas(L"Resource\\monkey_lane.xml");

	_inGameBg = &res.GetImage(L"Resource\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\InGame.xml");

	_tile1Img = &res.GetImage(L"Resource\\Tile1.png");

	_grid.Init(GRID_COUNT_X, GRID_COUNT_Y, BLOCK_SIZE);
	_tileMap.Init(GRID_COUNT_X, GRID_COUNT_Y); // 기본값 TileType::Path로 전체 채움
	_tileMap.GenerateRandomStartEndPoint();

	const Cell startCell = _tileMap.GetStartPoint();
	const Cell endCell = _tileMap.GetEndPoint();
	const int32 gridSize = _grid.GetGridSize();
	_path = PathFinder::FindPath(_tileMap, startCell, endCell, GRID_COUNT_X, GRID_COUNT_Y, gridSize);

	const Vector spawnPos(
		(startCell.iX + 0.5f) * gridSize,
		(startCell.iY + 0.5f) * gridSize);

	Bloon* bloon = BloonFactory::Create(BloonColor::Red, spawnPos, &_path);
	AddActor(bloon);
}

void GameScene::Render(Graphic& graphic)
{
	renderTileMap(graphic);

	const CellInfo* cell = _sprite->GetCell("angry_squirrel_arm_01");
	if (cell)
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 500.0f, *cell);
	}

	//const CellInfo* bgCell = _monkeyLaneSprite->GetCell("monkey_lane");
	//if (bgCell)
	//{
	//	const float scaleX = static_cast<float>(GameAreaWidth) / bgCell->w;
	//	const float scaleY = static_cast<float>(GameAreaHeight) / bgCell->h;
	//	const float bgScale = min(scaleX, scaleY);

	//	_monkeyLaneBg->DrawSprite(graphic, GameAreaCenterX, GameAreaCenterY, *bgCell, bgScale);
	//}

	renderGrid(graphic);

	renderStartEndDebug(graphic);

	Super::Render(graphic);
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
	Super::Cleanup();
}

void GameScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
