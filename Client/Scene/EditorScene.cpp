#include "pch.h"
#include "EditorScene.h"
#include "ResourceManager.h"

void EditorScene::Init(Graphic& graphic)
{
	ResourceManager& res = ResourceManager::GetInstance();
	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");
}

void EditorScene::Cleanup()
{
	Super::Cleanup();
}

void EditorScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void EditorScene::Render(Graphic& graphic)
{
	Super::Render(graphic);

	ResourceManager::GetInstance().GetImage(L"tack_shooter_baked").Draw(graphic, 400.0f, 200.0f, 1.0f, 0.0f);
	ResourceManager::GetInstance().GetImage(L"bomb_tower_baked").Draw(graphic, 400.0f, 400.0f, 1.0f, 0.0f);
	ResourceManager::GetInstance().GetImage(L"dart_monkey_baked").Draw(graphic, 400.0f, 600.0f, 1.0f, 0.0f);
	ResourceManager::GetInstance().GetImage(L"sniper_monkey_baked").Draw(graphic, 600.0f, 600.0f, 1.0f, 0.0f);



	/*if (const CellInfo* cell = _sprite->GetCell("sniper_arm"))
	{
		_inGameBg->DrawSprite(graphic, 695.0f, 640.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("dart_monkey_body"))
	{
		_inGameBg->DrawSprite(graphic, 700.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("sniper_green_hat"))
		 {
		_inGameBg->DrawSprite(graphic, 695.0f, 695.0f, *cell, 1.0f, 0.0f);
		}
	if (const CellInfo* cell = _sprite->GetCell("sniper_basic_rifle"))
	{
		_inGameBg->DrawSprite(graphic, 675.0f, 630.0f, *cell, 1.0f, 0.0f);
	}



	if (const CellInfo* cell = _sprite->GetCell("dart_monkey_arm_01"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 500.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("dart_monkey_body"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 500.0f, *cell, 1.0f, 0.0f);
	}*/

}

