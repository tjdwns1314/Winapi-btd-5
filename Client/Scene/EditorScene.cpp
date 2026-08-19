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

	_upgradeIconsImg = &res.GetImage(L"Resource\\Sprite\\upgrade_icons.png");
	_upgradeIconsSprite = &res.GetAtlas(L"Resource\\Sprite\\upgrade_icons.xml");

	_sharedSheetImg = &res.GetImage(L"Resource\\Sprite\\shared_sheet.png");
	_sharedSheetSprite = &res.GetAtlas(L"Resource\\Sprite\\shared_sheet.xml");

	_nukkiAutoplayImg = &res.GetImage(L"Resource\\Sprite\\nukki\\autoplay.png");
	_nukkiMusicImg = &res.GetImage(L"Resource\\Sprite\\nukki\\music.png");
	_nukkiReplayImg = &res.GetImage(L"Resource\\Sprite\\nukki\\replay.png");
	_nukkiResumeImg = &res.GetImage(L"Resource\\Sprite\\nukki\\resume.png");
	_nukkiSfxImg = &res.GetImage(L"Resource\\Sprite\\nukki\\sfx.png");
	_nukkiXImg = &res.GetImage(L"Resource\\Sprite\\nukki\\x.png");
	_nukkiCircleImg = &res.GetImage(L"Resource\\Sprite\\nukki\\circle_nukki.png");
	_nukkiTwoCircleImg = &res.GetImage(L"Resource\\Sprite\\nukki\\twocircle_nukki.png");
	_nukkiSmallCircleImg = &res.GetImage(L"Resource\\Sprite\\nukki\\smallcircle_nukki.png");
	_nukkiCogwheelImg = &res.GetImage(L"Resource\\Sprite\\nukki\\cogwheel_nukki.png");

	_loadingScreenImg = &res.GetImage(L"Resource\\Sprite\\loading_screen.png");
	_loadingScreenSprite = &res.GetAtlas(L"Resource\\Sprite\\loading_screen.xml");

	_newSharedImg = &res.GetImage(L"Resource\\Sprite\\newshared.png");
	_newSharedSprite = &res.GetAtlas(L"Resource\\Sprite\\newshared.xml");
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



	// 확보된 거)
	//if (const CellInfo* cell = _hudSprite->GetCell("side_hud_bg_01"))
	//{
	//	_hudImg->DrawSprite(graphic, 300.0f, 200.0f, *cell, 1.0f, 0.0f);
	//}
	// side_hud_bg_02
	//side_hud_scroll
	// "sell_box"
	// upgrade_box_buy
	// upgrade_box_cant
	// tower_thumbs_box
	//if (const CellInfo* cell = _hudSprite->GetCell("tower_thumbs_box"))
	//{
	//	_hudImg->DrawSprite(graphic, 300.0f, 400.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _hudSprite->GetCell("tower_profile_pic_box"))
	//{
	//	_hudImg->DrawSprite(graphic, 300.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}

	//// 원숭이 업그레이드 두건

	//if (const CellInfo* cell = _sprite->GetCell("red_bandana"))
	//{
	//	_inGameBg->DrawSprite(graphic, 400.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("blue_bandana"))
	//{
	//	_inGameBg->DrawSprite(graphic, 500.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("green_bandana"))
	//{
	//	_inGameBg->DrawSprite(graphic, 600.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("triple_darts_bandana"))
	//{
	//	_inGameBg->DrawSprite(graphic, 700.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}


	//// 압정 타워 애니메이션

	//if (const CellInfo* cell = _sprite->GetCell("tack_shooter_firing_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 100.0f, 300.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("tack_shooter_firing_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 200.0f, 300.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("tack_shooter_faster_firing_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 300.0f, 300.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("tack_shooter_faster_firing_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 400.0f, 300.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("tack_shooter_even_faster_logo"))
	//{
	//	_inGameBg->DrawSprite(graphic, 450.0f, 300.0f, *cell, 1.0f, 0.0f);
	//}
	//

	//if (const CellInfo* cell = _sprite->GetCell("tack_shooter_sprayer_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 500.0f, 300.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("tack_shooter_sprayer_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 600.0f, 300.0f, *cell, 1.0f, 0.0f);
	//}

	//// 저격총 원숭이 얘는 틴트 기능 넣어야함
	//if (const CellInfo* cell = _sprite->GetCell("sniper_goggles"))
	//{
	//	_inGameBg->DrawSprite(graphic, 100.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("sniper_full_metal_jacket"))
	//{
	//	_inGameBg->DrawSprite(graphic, 200.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}
	// sniper_laser
	// sniper_deadly_precision
	// sniper_semi_auto
	// sniper_full_metal_jacket

	//if (const CellInfo* cell = _sprite->GetCell("sniper_cripple_moab"))
	//{
	//	_inGameBg->DrawSprite(graphic, 200.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("sniper_green_hat"))
	//{
	//	_inGameBg->DrawSprite(graphic, 300.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}


	//// 저격총 애니메이션
	//if (const CellInfo* cell = _sprite->GetCell("sniper_arm_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 400.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("sniper_arm_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 500.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("sniper_arm_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 600.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("sniper_arm_04"))
	//{
	//	_inGameBg->DrawSprite(graphic, 700.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("sniper_arm_05"))
	//{
	//	_inGameBg->DrawSprite(graphic, 800.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}


	//// 저격총 탄피 애니메이션
	//if (const CellInfo* cell = _sprite->GetCell("sniper_casing_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 900.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("sniper_casing_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1000.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("sniper_casing_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1100.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("sniper_casing_04"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1200.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}





	//// 폭탄 애니메이션

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 100.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 200.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 300.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_04"))
	//{
	//	_inGameBg->DrawSprite(graphic, 400.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_silo"))
	//{
	//	_inGameBg->DrawSprite(graphic, 500.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_full"))
	//{
	//	_inGameBg->DrawSprite(graphic, 600.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}


	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 700.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 800.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 900.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_04"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1000.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//// 폭탄 타워 미사일 애니메이션
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1100.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1200.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1300.0f, 900.0f, *cell, 1.0f, 0.0f);
	//}
	//// 폭탄 타워 사일로 문 애니메이션
	//if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 100.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 200.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 300.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_04"))
	//{
	//	_inGameBg->DrawSprite(graphic, 400.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_05"))
	//{
	//	_inGameBg->DrawSprite(graphic, 500.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bommb_tower_silo_doors_06"))
	//{
	//	_inGameBg->DrawSprite(graphic, 600.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}
	//// 폭탄 타워 총구 연기 애니메이션
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_muzzle_smoke_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 600.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_muzzle_smoke_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 700.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_muzzle_smoke_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 800.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_muzzle_smoke_04"))
	//{
	//	_inGameBg->DrawSprite(graphic, 900.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//// 폭탄 타워 폭탄 애니메이션
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_bomb_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1000.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_bomb_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1100.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_bomb_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1200.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//// explosion 애니메이션
	//if (const CellInfo* cell = _sprite->GetCell("explosion_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1300.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("explosion_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1400.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("explosion_05"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1500.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("explosion_06"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1600.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_cluster_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 100.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_impact_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 200.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_missile_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 300.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_red_ring_04"))
	//{
	//	_inGameBg->DrawSprite(graphic, 400.0f, 700.0f, *cell, 1.0f, 0.0f);
	//}

	//// 별모양 bomb_tower_frag (애니메이션, bomb_tower_frag_01 ~ _04)
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_frag_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1000.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_frag_02"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1100.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_frag_03"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1200.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}
	//if (const CellInfo* cell = _sprite->GetCell("bomb_tower_frag_04"))
	//{
	//	_inGameBg->DrawSprite(graphic, 1300.0f, 100.0f, *cell, 1.0f, 0.0f);
	//}





	// 다트 원숭이 업그레이드 아이콘: 1경로(위쪽 행) / 2경로(아래쪽 행), 티어 1~4가 왼쪽에서 오른쪽으로 진행
	//auto drawUpgradeIcon = [&](const char* cellName, float x, float y)
	//	{
	//		if (const CellInfo* cell = _upgradeIconsSprite->GetCell(cellName))
	//		{
	//			_upgradeIconsImg->DrawSprite(graphic, x, y, *cell, 1.0f, 0.0f);
	//		}
	//	};

	//// 1경로: 날카로운 다트 -> 면도날 다트
	//drawUpgradeIcon("dart_monkey_sharp_shots_icon",     600.0f, 100.0f);
	//drawUpgradeIcon("dart_monkey_razor_icon",           700.0f, 100.0f);

	//// 2경로: 긴 사거리 다트 -> 강화된 시력 -> 트리플 다트
	//drawUpgradeIcon("dart_monkey_longer_range_icon",      600.0f, 200.0f);
	//drawUpgradeIcon("dart_monkey_enhanced_eyesight_icon", 700.0f, 200.0f);
	//drawUpgradeIcon("dart_monkey_triple_icon",            800.0f, 200.0f);

	//// 저격 원숭이: 1경로(풀 메탈 자켓 -> .50구경)
	//drawUpgradeIcon("sniper_full_metal_icon",        600.0f, 300.0f);
	//drawUpgradeIcon("sniper_point_50_icon",          700.0f, 300.0f);

	//// 저격 원숭이: 2경로(빠른 발사 -> 야간 투시경)
	//drawUpgradeIcon("sniper_faster_firing_icon",     600.0f, 400.0f);
	//drawUpgradeIcon("sniper_nvg_icon",               700.0f, 400.0f);

	//// 압정 슈터: 1경로(빠른 발사 -> 더 빠른 발사 -> 압정 분무기)
	//drawUpgradeIcon("tack_shooter_faster_firing_icon",      600.0f, 500.0f);
	//drawUpgradeIcon("tack_shooter_even_faster_firing_icon", 700.0f, 500.0f);
	//drawUpgradeIcon("tack_shooter_sprayer_icon",            800.0f, 500.0f);

	//// 압정 슈터: 2경로(사거리 증가 -> 슈퍼 사거리)
	//drawUpgradeIcon("tack_shooter_extra_range_icon",   600.0f, 600.0f);
	//drawUpgradeIcon("tack_shooter_super_range_icon",   700.0f, 600.0f);

	//// 폭탄 타워: 1경로(사거리 증가 -> 파편 폭탄)
	//drawUpgradeIcon("bomb_extra_range_icon", 600.0f, 700.0f);
	//drawUpgradeIcon("bomb_frag_icon",        700.0f, 700.0f);

	//// 폭탄 타워: 2경로(더 큰 폭탄 -> 미사일 발사기)
	//drawUpgradeIcon("bomb_bigger_icon",  600.0f, 800.0f);
	//drawUpgradeIcon("bomb_missile_icon", 700.0f, 800.0f);

	/*if (const CellInfo* cell = _sprite->GetCell("banana_box"))
{
	_inGameBg->DrawSprite(graphic, 600.0f, 500.0f, *cell, 1.0f, 0.0f);
}*/
//graphic.DrawString(L"안녕하세요", 
//	D2D1::RectF(50.0f, 50.0f, 400.0f, 100.0f), 
//	FONT_30, 
//	D2D1::ColorF(D2D1::ColorF::White));




//	// start 버튼 후보 4종 비교용 (미검증 - 실제 색상 확인 필요)
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

// shared_sheet 아이콘 확인용 (임시)
//auto drawSharedIcon = [&](const char* cellName, float x, float y)
//	{
//		if (const CellInfo* cell = _sharedSheetSprite->GetCell(cellName))
//		{
//			_sharedSheetImg->DrawSprite(graphic, x, y, *cell, 1.0f, 0.0f);
//		}
//	};

//drawSharedIcon("resume", 100.0f, 100.0f);
//drawSharedIcon("double_mm_icon_small", 200.0f, 100.0f);
//drawSharedIcon("sound", 300.0f, 100.0f);
//drawSharedIcon("info", 400.0f, 100.0f);
//drawSharedIcon("home", 500.0f, 100.0f);
//drawSharedIcon("music", 600.0f, 100.0f);
//drawSharedIcon("stroke", 700.0f, 100.0f);
//drawSharedIcon("load_icon_shared", 800.0f, 100.0f);

// nukki 아이콘 확인용 (임시, 아틀라스 없이 낱개 이미지)
//_nukkiAutoplayImg->Draw(graphic, 100.0f, 200.0f, 1.0f, 0.0f);
//_nukkiMusicImg->Draw(graphic, 200.0f, 200.0f, 1.0f, 0.0f);
//_nukkiReplayImg->Draw(graphic, 300.0f, 200.0f, 1.0f, 0.0f);
//_nukkiResumeImg->Draw(graphic, 400.0f, 200.0f, 1.0f, 0.0f);
//_nukkiSfxImg->Draw(graphic, 500.0f, 200.0f, 1.0f, 0.0f);
//_nukkiXImg->Draw(graphic, 600.0f, 200.0f, 0.25f, 0.0f);



// loading_screen 아이콘 확인용 (임시)
	for (int i = 0; i < 10; ++i)
	{
		if (const CellInfo* cell = _loadingScreenSprite->GetCell("wooden_slat"))
		{
			_loadingScreenImg->DrawSprite(graphic, 900.0f, 60.0f + i * 105.0f, *cell, 7.0f, 0.0f, false, 0.60f);
		}
	}
	if (const CellInfo* cell = _loadingScreenSprite->GetCell("btd5_text_upper"))
	{
		_loadingScreenImg->DrawSprite(graphic, 880.0f, 455.0f, *cell, 0.5f, 0.0f);
	}
	if (const CellInfo* cell = _loadingScreenSprite->GetCell("btd5_text_lower"))
	{
		_loadingScreenImg->DrawSprite(graphic, 880.0f, 590.0f, *cell, 0.5f, 0.0f);
	}

	// 원형 장식: 사진처럼 대략 배치 (중앙 하단 스피너 / 표지판 옆 코인 / 좌하단 장식)
	_nukkiSmallCircleImg->Draw(graphic, 880.0f, 800.0f, 0.5f, 0.0f);
	_nukkiCircleImg->Draw(graphic, 1600.0f, 100.0f, 1.0f, 0.0f);
	_nukkiTwoCircleImg->Draw(graphic, 260.0f, 1000.0f, 2.0f, 0.0f);

	// cogwheel 3번 렌더: 우상단 큰 톱니바퀴 / 좌하단 큰 톱니바퀴 / 좌하단 겹친 작은 톱니바퀴
	_nukkiCogwheelImg->Draw(graphic, 1600.0f, 80.0f, 0.4f, 0.0f);
	_nukkiCogwheelImg->Draw(graphic, 80.0f, 850.0f, 0.4f, 0.0f);
	_nukkiCogwheelImg->Draw(graphic, 430.0f, 1100.0f, 0.4f, 0.0f);

	// btd5_text_upper
	// btd5_text_lower

	// InGame.xml 이펙트 스프라이트 전체 미리보기 (요청: 화면 제일 위에 그려서 모두 보이게)
	auto drawEffectRow = [&](const std::vector<const char*>& cellNames, float y)
		{
			float x = 50.0f;
			for (const char* cellName : cellNames)
			{
				if (const CellInfo* cell = _sprite->GetCell(cellName))
				{
					_inGameBg->DrawSprite(graphic, x, y, *cell, 1.0f, 0.0f);
				}
				x += 90.0f;
			}
		};

	drawEffectRow({ "bomb_tower_muzzle_smoke_01", "bomb_tower_muzzle_smoke_02", "bomb_tower_muzzle_smoke_03", "bomb_tower_muzzle_smoke_04" }, 50.0f);
	drawEffectRow({ "bomb_tower_bomb_01", "bomb_tower_bomb_02", "bomb_tower_bomb_03" }, 140.0f);
	/*drawEffectRow({ "bomb_tower_missile_01", "bomb_tower_missile_02", "bomb_tower_missile_03" }, 230.0f);
	drawEffectRow({ "bomb_tower_frag_01", "bomb_tower_frag_02", "bomb_tower_frag_03", "bomb_tower_frag_04" }, 320.0f);
	drawEffectRow({ "bomb_tower_impact_01", "bomb_tower_impact_02", "bomb_tower_impact_03", "bomb_tower_impact_04" }, 410.0f);
	drawEffectRow({ "bomb_tower_cluster_01", "bomb_tower_cluster_02", "bomb_tower_cluster_03", "bomb_tower_cluster_04" }, 500.0f);
	drawEffectRow({ "bomb_tower_red_ring_01", "bomb_tower_red_ring_02", "bomb_tower_red_ring_03", "bomb_tower_red_ring_04" }, 590.0f);*/
	//drawEffectRow({ "explosion_01", "explosion_02", "explosion_05", "explosion_06" }, 680.0f);
	drawEffectRow({ "napalm_explosion_01", "napalm_explosion_02", "napalm_explosion_03", "napalm_explosion_04", "napalm_explosion_05" }, 770.0f);
	//drawEffectRow({ "ice_explosion_01", "ice_explosion_02", "ice_explosion_03", "ice_explosion_04", "ice_explosion_05" }, 860.0f);
	//drawEffectRow({ "smoke_01", "smoke_02", "smoke_03" }, 950.0f);
	//drawEffectRow({ "pop" }, 1040.0f);

	if (const CellInfo* cell = _hudSprite->GetCell("target_box"))
	{
		_hudImg->DrawSprite(graphic, 800.0f, 200.0f, *cell, 1.0f, 0.0f);
	}



	if (const CellInfo* cell = _sprite->GetCell("bloonsday_pro_ball_shields"))
	{
		_inGameBg->DrawSprite(graphic, 400.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	if (const CellInfo* cell = _sprite->GetCell("candy_chimney_02"))
	{
		_inGameBg->DrawSprite(graphic, 500.0f, 500.0f, *cell, 1.0f, 0.0f);
	}

	//if (const CellInfo* cell = _sprite->GetCell("candy_chimney_01"))
	//{
	//	_inGameBg->DrawSprite(graphic, 600.0f, 500.0f, *cell, 1.0f, 0.0f);
	//}



	// newshared.png 양피지 패널 5종 미리보기
	auto drawNewShared = [&](const char* cellName, float x, float y)
		{
			if (const CellInfo* cell = _newSharedSprite->GetCell(cellName))
			{
				_newSharedImg->DrawSprite(graphic, x, y, *cell, 1.0f, 0.0f);
			}
		};

	drawNewShared("newshared_parchment",       100.0f, 200.0f);
	drawNewShared("newshared_parchment_top",    450.0f, 200.0f);
	drawNewShared("newshared_parchment_mid",    450.0f, 260.0f);
	drawNewShared("newshared_parchment_bottom", 450.0f, 300.0f);
	drawNewShared("newshared_mini_parchment",   850.0f, 200.0f);
}

