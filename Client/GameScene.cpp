#include "pch.h"
#include "GameScene.h"

void GameScene::Init(Graphic& graphic)
{
	Super::Init(graphic);

	_inGameBg.Load(graphic, L"Res\\InGame.png");
	_sprite.LoadXml(L"Res\\InGame.xml");
}

void GameScene::Render(Graphic& graphic)
{
	const CellInfo* cell = _sprite.GetCell("angry_squirrel_arm_01");
	if (cell)
	{
		_inGameBg.DrawCell(graphic, 500.0f, 500.0f, *cell);
	}
	//_inGameBg.Draw(graphic, 0.0f, 0.0f);

	// 씬이 소유한 액터들을 레이어 순서대로 렌더링
	Super::Render(graphic);
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
