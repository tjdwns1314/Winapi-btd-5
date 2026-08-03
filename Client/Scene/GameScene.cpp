#include "pch.h"
#include "GameScene.h"

void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);
	_RealGameBG.Load(graphic, L"Resource\\monkey_lane_thumb.jpg");
	_inGameBg.Load(graphic, L"Resource\\InGame.png");
	_sprite.LoadXml(L"Resource\\InGame.xml");

	_grid.Init(GRID_COUNT_X, GRID_COUNT_Y, BLOCK_SIZE);
}

void GameScene::Render(Graphic& graphic)
{
	const CellInfo* cell = _sprite.GetCell("angry_squirrel_arm_01");
	if (cell)
	{
		_inGameBg.DrawCell(graphic, 500.0f, 500.0f, *cell);
	}
	//_inGameBg.Draw(graphic, 0.0f, 0.0f);
	D2D1_SIZE_F bgSize = _RealGameBG.GetSize();
	float drawX = GameAreaCenterX - bgSize.width * 0.5f;
	float drawY = GameAreaCenterY - bgSize.height * 0.5f;
	_RealGameBG.Draw(graphic, drawX, drawY);
	renderGrid(graphic);

	// 씬이 소유한 액터들을 레이어 순서대로 렌더링
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

	Super::Cleanup();
}

void GameScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
