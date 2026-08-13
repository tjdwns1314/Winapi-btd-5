#include "pch.h"
#include "EditorScene.h"
#include "ResourceManager.h"

void EditorScene::Init(Graphic& graphic)
{
	ResourceManager& res = ResourceManager::GetInstance();
	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");

	_hudImg = &res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");

	_popupImg = &res.GetImage(L"Resource\\Sprite\\game_over_popup.png");
	_popupSprite = &res.GetAtlas(L"Resource\\Sprite\\game_over_popup.xml");
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








	if (const CellInfo* cell = _sprite->GetCell("banana_farm_tree"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("banana_box"))
	{
		_inGameBg->DrawSprite(graphic, 600.0f, 500.0f, *cell, 1.0f, 0.0f);
	}




	graphic.DrawTextW(L"안녕하세요", 
		D2D1::RectF(50.0f, 50.0f, 400.0f, 100.0f), 
		FONT_30, 
		D2D1::ColorF(D2D1::ColorF::White));




		// start 버튼 후보 4종 비교용 (미검증 - 실제 색상 확인 필요)
		if (const CellInfo* cell = _hudSprite->GetCell("play_icon"))
		 {
		_hudImg->DrawSprite(graphic, 800.0f, 200.0f, *cell, 1.0f, 0.0f);
		}
	 if (const CellInfo* cell = _hudSprite->GetCell("ff_icon"))
		 {
		_hudImg->DrawSprite(graphic, 950.0f, 200.0f, *cell, 1.0f, 0.0f);
		}
	 if (const CellInfo* cell = _hudSprite->GetCell("ff_icon_red"))
		 {
		_hudImg->DrawSprite(graphic, 1100.0f, 200.0f, *cell, 1.0f, 0.0f);
		}
	 if (const CellInfo* cell = _hudSprite->GetCell("ff_icon_locked"))
		 {
		_hudImg->DrawSprite(graphic, 1250.0f, 200.0f, *cell, 1.0f, 0.0f);
		}

	 if (const CellInfo* cell = _hudSprite->GetCell("pause_icon"))
	 {
		 _hudImg->DrawSprite(graphic, 1400.0f, 200.0f, *cell, 1.0f, 0.0f);
	 }

	 if (const CellInfo* cell = _hudSprite->GetCell("plain_button"))
	 {
		 _hudImg->DrawSprite(graphic, 1500.0f, 200.0f, *cell, 1.0f, 0.0f);
	 }

	 if (const CellInfo* cell = _popupSprite->GetCell("try_again_icon"))
	 {
		 _popupImg->DrawSprite(graphic, 1500.0f, 200.0f, *cell, 1.0f, 0.0f);
	 }

	ResourceManager::GetInstance().GetImage(L"restart_button_baked").Draw(graphic, 1650.0f, 200.0f, 1.0f, 0.0f);

}

