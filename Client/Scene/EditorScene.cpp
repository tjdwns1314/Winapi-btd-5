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

	//ResourceManager::GetInstance().GetImage(L"tack_shooter_baked").Draw(graphic, 400.0f, 200.0f, 1.0f, 0.0f);
	//ResourceManager::GetInstance().GetImage(L"bomb_tower_baked").Draw(graphic, 400.0f, 400.0f, 1.0f, 0.0f);
	//ResourceManager::GetInstance().GetImage(L"dart_monkey_baked").Draw(graphic, 400.0f, 600.0f, 1.0f, 0.0f);
	//ResourceManager::GetInstance().GetImage(L"sniper_monkey_baked").Draw(graphic, 600.0f, 600.0f, 1.0f, 0.0f);







	// 원숭이 팔 애니메이션 
	if (const CellInfo* cell = _sprite->GetCell("dart_monkey_arm_01"))
	{
		_inGameBg->DrawSprite(graphic, 100.0f, 100.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("dart_monkey_arm_02"))
	{
		_inGameBg->DrawSprite(graphic, 200.0f, 100.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("dart_monkey_arm_03"))
	{
		_inGameBg->DrawSprite(graphic, 300.0f, 100.0f, *cell, 1.0f, 0.0f);
	}

	// 원숭이 업그레이드 두건

	if (const CellInfo* cell = _sprite->GetCell("red_bandana"))
	{
		_inGameBg->DrawSprite(graphic, 400.0f, 100.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("blue_bandana"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 100.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("green_bandana"))
	{
		_inGameBg->DrawSprite(graphic, 600.0f, 100.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("triple_darts_bandana"))
	{
		_inGameBg->DrawSprite(graphic, 700.0f, 100.0f, *cell, 1.0f, 0.0f);
	}


	// 압정 타워 애니메이션

	if (const CellInfo* cell = _sprite->GetCell("tack_shooter_firing_01"))
	{
		_inGameBg->DrawSprite(graphic, 100.0f, 300.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("tack_shooter_firing_02"))
	{
		_inGameBg->DrawSprite(graphic, 200.0f, 300.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("tack_shooter_faster_firing_01"))
	{
		_inGameBg->DrawSprite(graphic, 300.0f, 300.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("tack_shooter_faster_firing_02"))
	{
		_inGameBg->DrawSprite(graphic, 400.0f, 300.0f, *cell, 1.0f, 0.0f);
	}


	if (const CellInfo* cell = _sprite->GetCell("tack_shooter_sprayer_01"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 300.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("tack_shooter_sprayer_02"))
	{
		_inGameBg->DrawSprite(graphic, 600.0f, 300.0f, *cell, 1.0f, 0.0f);
	}

	// 저격총 원숭이 얘는 틴트 기능 넣어야함
	if (const CellInfo* cell = _sprite->GetCell("sniper_goggles"))
	{
		_inGameBg->DrawSprite(graphic, 100.0f, 500.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("sniper_shades"))
	{
		_inGameBg->DrawSprite(graphic, 200.0f, 500.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("sniper_green_hat"))
	{
		_inGameBg->DrawSprite(graphic, 300.0f, 500.0f, *cell, 1.0f, 0.0f);
	}
	// 저격총 애니메이션
	if (const CellInfo* cell = _sprite->GetCell("sniper_arm_01"))
	{
		_inGameBg->DrawSprite(graphic, 400.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("sniper_arm_02"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("sniper_arm_03"))
	{
		_inGameBg->DrawSprite(graphic, 600.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("sniper_arm_04"))
	{
		_inGameBg->DrawSprite(graphic, 700.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("sniper_arm_05"))
	{
		_inGameBg->DrawSprite(graphic, 800.0f, 500.0f, *cell, 1.0f, 0.0f);
	}


	// 저격총 탄피 애니메이션
	if (const CellInfo* cell = _sprite->GetCell("sniper_casing_01"))
	{
		_inGameBg->DrawSprite(graphic, 900.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("sniper_casing_02"))
	{
		_inGameBg->DrawSprite(graphic, 1000.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("sniper_casing_03"))
	{
		_inGameBg->DrawSprite(graphic, 1100.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("sniper_casing_04"))
	{
		_inGameBg->DrawSprite(graphic, 1200.0f, 500.0f, *cell, 1.0f, 0.0f);
	}





	// 폭탄 애니메이션

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_01"))
	{
		_inGameBg->DrawSprite(graphic, 100.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_02"))
	{
		_inGameBg->DrawSprite(graphic, 200.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_03"))
	{
		_inGameBg->DrawSprite(graphic, 300.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_04"))
	{
		_inGameBg->DrawSprite(graphic, 400.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_silo"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_full"))
	{
		_inGameBg->DrawSprite(graphic, 600.0f, 900.0f, *cell, 1.0f, 0.0f);
	}


	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_01"))
	{
		_inGameBg->DrawSprite(graphic, 700.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_02"))
	{
		_inGameBg->DrawSprite(graphic, 800.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_03"))
	{
		_inGameBg->DrawSprite(graphic, 900.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_04"))
	{
		_inGameBg->DrawSprite(graphic, 1000.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	// 폭탄 타워 미사일 애니메이션
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_01"))
	{
		_inGameBg->DrawSprite(graphic, 1100.0f, 900.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_02"))
	{
		_inGameBg->DrawSprite(graphic, 1200.0f, 900.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_03"))
	{
		_inGameBg->DrawSprite(graphic, 1300.0f, 900.0f, *cell, 1.0f, 0.0f);
	}
	// 폭탄 타워 사일로 문 애니메이션
	if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_01"))
	{
		_inGameBg->DrawSprite(graphic, 100.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_02"))
	{
		_inGameBg->DrawSprite(graphic, 200.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_03"))
	{
		_inGameBg->DrawSprite(graphic, 300.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_04"))
	{
		_inGameBg->DrawSprite(graphic, 400.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_05"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_06"))
	{
		_inGameBg->DrawSprite(graphic, 600.0f, 700.0f, *cell, 1.0f, 0.0f);
	}
	// 폭탄 타워 총구 연기 애니메이션
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_muzzle_smoke_01"))
	{
		_inGameBg->DrawSprite(graphic, 600.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_muzzle_smoke_02"))
	{
		_inGameBg->DrawSprite(graphic, 700.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_muzzle_smoke_03"))
	{
		_inGameBg->DrawSprite(graphic, 800.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_muzzle_smoke_04"))
	{
		_inGameBg->DrawSprite(graphic, 900.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	// 폭탄 타워 폭탄 애니메이션
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_bomb_01"))
	{
		_inGameBg->DrawSprite(graphic, 1000.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_bomb_02"))
	{
		_inGameBg->DrawSprite(graphic, 1100.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_bomb_03"))
	{
		_inGameBg->DrawSprite(graphic, 1200.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	// explosion 애니메이션
	if (const CellInfo* cell = _sprite->GetCell("explosion_01"))
	{
		_inGameBg->DrawSprite(graphic, 1300.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("explosion_02"))
	{
		_inGameBg->DrawSprite(graphic, 1400.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("explosion_05"))
	{
		_inGameBg->DrawSprite(graphic, 1500.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("explosion_06"))
	{
		_inGameBg->DrawSprite(graphic, 1600.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_red_ring_01"))
	{
		_inGameBg->DrawSprite(graphic, 100.0f, 700.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_red_ring_02"))
	{
		_inGameBg->DrawSprite(graphic, 200.0f, 700.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_red_ring_03"))
	{
		_inGameBg->DrawSprite(graphic, 300.0f, 700.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_red_ring_04"))
	{
		_inGameBg->DrawSprite(graphic, 400.0f, 700.0f, *cell, 1.0f, 0.0f);
	}

	// 별모양 bomb_tower_frag (애니메이션, bomb_tower_frag_01 ~ _04)
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_frag_01"))
	{
		_inGameBg->DrawSprite(graphic, 1000.0f, 100.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_frag_02"))
	{
		_inGameBg->DrawSprite(graphic, 1100.0f, 100.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_frag_03"))
	{
		_inGameBg->DrawSprite(graphic, 1200.0f, 100.0f, *cell, 1.0f, 0.0f);
	}
	if (const CellInfo* cell = _sprite->GetCell("bomb_tower_frag_04"))
	{
		_inGameBg->DrawSprite(graphic, 1300.0f, 100.0f, *cell, 1.0f, 0.0f);
	}





	/*if (const CellInfo* cell = _sprite->GetCell("banana_box"))
{
	_inGameBg->DrawSprite(graphic, 600.0f, 500.0f, *cell, 1.0f, 0.0f);
}*/
	//graphic.DrawString(L"안녕하세요", 
	//	D2D1::RectF(50.0f, 50.0f, 400.0f, 100.0f), 
	//	FONT_30, 
	//	D2D1::ColorF(D2D1::ColorF::White));




	//	// start 버튼 후보 4종 비교용 (미검증 - 실제 색상 확인 필요)
	//	if (const CellInfo* cell = _hudSprite->GetCell("play_icon"))
	//	 {
	//	_hudImg->DrawSprite(graphic, 800.0f, 200.0f, *cell, 1.0f, 0.0f);
	//	}
	// if (const CellInfo* cell = _hudSprite->GetCell("ff_icon"))
	//	 {
	//	_hudImg->DrawSprite(graphic, 950.0f, 200.0f, *cell, 1.0f, 0.0f);
	//	}
	// if (const CellInfo* cell = _hudSprite->GetCell("ff_icon_red"))
	//	 {
	//	_hudImg->DrawSprite(graphic, 1100.0f, 200.0f, *cell, 1.0f, 0.0f);
	//	}
	// if (const CellInfo* cell = _hudSprite->GetCell("ff_icon_locked"))
	//	 {
	//	_hudImg->DrawSprite(graphic, 1250.0f, 200.0f, *cell, 1.0f, 0.0f);
	//	}

	// if (const CellInfo* cell = _hudSprite->GetCell("pause_icon"))
	// {
	//	 _hudImg->DrawSprite(graphic, 1400.0f, 200.0f, *cell, 1.0f, 0.0f);
	// }

	// if (const CellInfo* cell = _hudSprite->GetCell("plain_button"))
	// {
	//	 _hudImg->DrawSprite(graphic, 1500.0f, 200.0f, *cell, 1.0f, 0.0f);
	// }

	// if (const CellInfo* cell = _popupSprite->GetCell("try_again_icon"))
	// {
	//	 _popupImg->DrawSprite(graphic, 1500.0f, 200.0f, *cell, 1.0f, 0.0f);
	// }

	//ResourceManager::GetInstance().GetImage(L"restart_button_baked").Draw(graphic, 1650.0f, 200.0f, 1.0f, 0.0f);

}

