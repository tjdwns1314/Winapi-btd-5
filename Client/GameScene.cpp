#include "pch.h"
#include "GameScene.h"

void GameScene::Init(Graphic& graphic)
{
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

}
void GameScene::Release()
{
	_inGameBg.Release();
}
void GameScene::Update()
{

}
