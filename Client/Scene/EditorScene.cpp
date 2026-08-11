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

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_wheel"))
		 {
		_inGameBg->DrawSprite(graphic, 700.0f, 700.0f, *cell, 1.0f, 0.0f);
		}
}

