#include "pch.h"
#include "GameScene.h"

void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);
	_monkeyLaneBg.Load(graphic, L"Resource\\monkey_lane.png");
	_monkeyLaneSprite.LoadXml(L"Resource\\monkey_lane.xml");

	_inGameBg.Load(graphic, L"Resource\\InGame.png");
	_sprite.LoadXml(L"Resource\\InGame.xml");

	_bloonImg.Load(graphic, L"Resource\\bloonImg.png");

	_grid.Init(GRID_COUNT_X, GRID_COUNT_Y, BLOCK_SIZE);
}

void GameScene::Render(Graphic& graphic)
{
	const CellInfo* cell = _sprite.GetCell("angry_squirrel_arm_01");
	if (cell)
	{
		_inGameBg.DrawCell(graphic, 500.0f, 500.0f, *cell);
	}

	const CellInfo* bgCell = _monkeyLaneSprite.GetCell("monkey_lane");
	if (bgCell)
	{
		const float scaleX = static_cast<float>(GameAreaWidth) / bgCell->w;
		const float scaleY = static_cast<float>(GameAreaHeight) / bgCell->h;
		const float bgScale = min(scaleX, scaleY);

		float drawX = GameAreaCenterX - bgCell->w * bgScale * 0.5f;
		float drawY = GameAreaCenterY - bgCell->h * bgScale * 0.5f;
		_monkeyLaneBg.DrawCell(graphic, drawX, drawY, *bgCell, bgScale);
	}

	_bloonImg.Draw(graphic, static_cast<float>(GameAreaCenterX), static_cast<float>(GameAreaCenterY));

	renderGrid(graphic);

	Super::Render(graphic);
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

void GameScene::Cleanup()
{
	_inGameBg.Release();
	_monkeyLaneBg.Release();

	Super::Cleanup();
}

void GameScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
