#include "pch.h"
#include "GameAssets.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "SpriteBaker.h"

void GameAssets::Load(Graphic& graphic)
{
	ResourceManager& res = ResourceManager::GetInstance();

	// Resource\Bgm 안의 모든 .wav(배경음 6곡 + 효과음)를 파일명 기준으로 캐싱한다.
	AudioManager::GetInstance().LoadSoundsInDirectory(L"Resource\\Bgm");

	res.LoadImage(graphic, L"Resource\\Sprite\\InGame.png");
	res.LoadAtlas(L"Resource\\Sprite\\InGame.xml");

	res.LoadImage(graphic, L"Resource\\Tile\\Tile1_pipo.png");
	res.LoadImage(graphic, L"Resource\\Tile\\Tile2_pipo.png");

	res.LoadImage(graphic, L"Resource\\Sprite\\in_game_hud.png");
	res.LoadAtlas(L"Resource\\Sprite\\in_game_hud.xml");

	res.LoadImage(graphic, L"Resource\\Sprite\\game_over_popup.png");
	res.LoadAtlas(L"Resource\\Sprite\\game_over_popup.xml");

	res.LoadImage(graphic, L"Resource\\Sprite\\upgrade_icons.png");
	res.LoadAtlas(L"Resource\\Sprite\\upgrade_icons.xml");

	res.LoadImage(graphic, L"Resource\\Sprite\\shared_sheet.png");
	res.LoadAtlas(L"Resource\\Sprite\\shared_sheet.xml");

	res.LoadImage(graphic, L"Resource\\Sprite\\newshared.png");
	res.LoadAtlas(L"Resource\\Sprite\\newshared.xml");

	res.LoadImage(graphic, L"Resource\\Image_png\\lobby_background.png");

	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\autoplay.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\music.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\replay.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\resume.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\save.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\sfx.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\x.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\circle_nukki.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\twocircle_nukki.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\smallcircle_nukki.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\cogwheel_nukki.png");
	res.LoadImage(graphic, L"Resource\\Sprite\\nukki\\gold_trophy_nukki.png");

	res.LoadImage(graphic, L"Resource\\Sprite\\loading_screen.png");
	res.LoadAtlas(L"Resource\\Sprite\\loading_screen.xml");

	res.LoadImage(graphic, L"Resource\\Red.png");
	res.LoadImage(graphic, L"Resource\\Blue.png");
	res.LoadImage(graphic, L"Resource\\Green.png");
	res.LoadImage(graphic, L"Resource\\Yellow.png");
	res.LoadImage(graphic, L"Resource\\Pink.png");
	res.LoadImage(graphic, L"Resource\\Black.png");
	res.LoadImage(graphic, L"Resource\\White.png");
	res.LoadImage(graphic, L"Resource\\Lead.png");
	res.LoadImage(graphic, L"Resource\\Zebra.png");
	res.LoadImage(graphic, L"Resource\\Rainbow.png");
	res.LoadImage(graphic, L"Resource\\Ceramic.png");

	SpriteBaker baker(res.GetImage(L"Resource\\Sprite\\InGame.png"), res.GetAtlas(L"Resource\\Sprite\\InGame.xml"));


	auto bakeDartMonkeyThrow = [&](const wchar_t* keyPrefix, const char* bandanaCell, D2D1_POINT_2F bandanaOffset = { 0.0f, 0.0f })
		{
			std::vector<BakeFrame> frames;
			char armCells[3][32];
			for (int i = 1; i <= 3; ++i)
			{
				sprintf_s(armCells[i - 1], "dart_monkey_arm_%02d", i);

				BakeFrame frame =
				{
				{.cellName = armCells[i - 1],.offset = {2.0f,0.0f} },
				{.cellName = "dart_monkey_body",.offset = {7.5f,10.0f} },
				};
				if (bandanaCell != nullptr)

				frame.push_back({ .cellName = bandanaCell,.offset = bandanaOffset });

				frames.push_back(std::move(frame));
				}

				baker.BakeAnimation(res, graphic, keyPrefix, { 125.0f, 140.0f }, frames);
			};

		bakeDartMonkeyThrow(L"dart_monkey_base_baked", nullptr);
		bakeDartMonkeyThrow(L"dart_monkey_blue_baked", "blue_bandana", { 0.0f, -11.0f });
		bakeDartMonkeyThrow(L"dart_monkey_green_baked", "green_bandana", { 0.0f, -11.0f });
		bakeDartMonkeyThrow(L"dart_monkey_red_baked", "red_bandana", { 0.0f, -11.0f });
		bakeDartMonkeyThrow(L"dart_monkey_triple_baked", "triple_darts_bandana", { -9.5f, 10.0f });

	// 압정 다트 던지기 애니메이션: firing 셀이 _01→_02로 바뀌는 게 애니메이션이고,
	// _02 재생이 끝나면 발사된다(Tower::updateThrowAnimation). 3등급 이상 커지는 크기는
	// 이미지가 아니라 Tower::ApplyUpgrade의 GetTowerGradeScale(렌더 스케일)로 처리한다.
	auto bakeTackShooterThrow = [&](const wchar_t* keyPrefix, const char* firingCellPrefix,
		const char* logoCell, bool logoMirrored)
	{
		std::vector<BakeFrame> frames;
		char firingCells[2][64]; // 루프 밖 선언 필수 — cellName은 포인터만 저장하므로 루프 안에서 매번 새로 선언하면 dangling.

		for (int i = 1; i <= 2; ++i)
		{
			sprintf_s(firingCells[i - 1], "%s_%02d", firingCellPrefix, i);
			const char* firingCell = firingCells[i - 1];

			BakeFrame frame =
			{
				{ .cellName = firingCell, .anchor = BakeAnchor::TopLeft },
				{ .cellName = firingCell, .anchor = BakeAnchor::TopRight,    .flipX = true },
				{ .cellName = firingCell, .anchor = BakeAnchor::BottomLeft,  .angle = 180.0f, .flipX = true },
				{ .cellName = firingCell, .anchor = BakeAnchor::BottomRight, .angle = 180.0f },
				{ .cellName = "tack_shooter_base", .anchor = BakeAnchor::Left },
				{ .cellName = "tack_shooter_base", .anchor = BakeAnchor::Right, .flipX = true },
			};

			if (logoMirrored)
			{
				frame.push_back({ .cellName = logoCell, .anchor = BakeAnchor::Left });
				frame.push_back({ .cellName = logoCell, .anchor = BakeAnchor::Right, .flipX = true });
			}
			else
			{
				frame.push_back({ .cellName = logoCell }); // 앵커 없음 = Center 1개
			}

			frames.push_back(std::move(frame));
		}
		baker.BakeAnimation(res, graphic, keyPrefix, { 200.0f, 200.0f }, frames);
	};

	// 1단계: firing + tack_logo(좌우대칭)
	bakeTackShooterThrow(L"tack_shooter_grade1_baked", "tack_shooter_firing",        "tack_shooter_tack_logo",        true);
	// 2단계(=3단계 공용): firing + even_faster_logo(Center). 3단계는 GetTowerGradeScale로 렌더 크기만 커짐.
	bakeTackShooterThrow(L"tack_shooter_grade2_baked", "tack_shooter_firing",        "tack_shooter_even_faster_logo", false);
	// 4단계: faster_firing 셀로 교체
	bakeTackShooterThrow(L"tack_shooter_grade4_baked", "tack_shooter_faster_firing", "tack_shooter_even_faster_logo", false);
	// 5단계: sprayer 셀로 교체
	bakeTackShooterThrow(L"tack_shooter_grade5_baked", "tack_shooter_sprayer",       "tack_shooter_even_faster_logo", false);



	// 저격원숭이: 등급마다 idle(bolt_action) 1장 + 발사 애니메이션(arm_01~05, 01~04엔 탄피 동반) 5장을 굽는다.
	auto bakeSniperMonkey = [&](const wchar_t* keyPrefix, const BakeFrame& accessories)
	{
		BakeFrame idleFrame =
		{
			{.cellName = "sniper_arm",         .offset = {2.0f, -50.0f} },
			{.cellName = "dart_monkey_body", .offset = {7.0f,10.0f} },
			{.cellName = "sniper_basic_rifle", .offset = {-18.0f, -60.0f} },
			{.cellName = "sniper_basic_rifle_muzzle", .offset = {-18.0f, -100.0f} },
			{.cellName = "sniper_bolt_action", .offset = {-31.0f, -48.0f} },
		};
		idleFrame.insert(idleFrame.end(), accessories.begin(), accessories.end());

		wchar_t idleKey[128];
		swprintf_s(idleKey, L"%s_idle", keyPrefix);
		baker.Bake(res, graphic, idleKey, { 140.0f, 230.0f }, idleFrame);

		std::vector<BakeFrame> throwFrames;
		char armCells[5][32];
		char casingCells[4][32]; // 루프 밖 선언 필수 — cellName은 포인터만 저장하므로 dangling 방지.

		for (int i = 1; i <= 5; ++i)
		{
			sprintf_s(armCells[i - 1], "sniper_arm_%02d", i);

			BakeFrame frame =
			{
				{.cellName = armCells[i - 1], .offset = {-30.0f, -30.0f} }, // TODO(미검증): 전 프레임 동일 오프셋, 실제 확인 후 조정
				{.cellName = "dart_monkey_body", .offset = {7.0f, 10.0f} },
				{.cellName = "sniper_basic_rifle", .offset = {-18.0f, -60.0f} },
			};
			frame.insert(frame.end(), accessories.begin(), accessories.end());

			if (i >= 2) // 쏘는 순간(arm_01)엔 탄피가 아직 안 나오므로 arm_02부터 casing_01 시작.
			{
				sprintf_s(casingCells[i - 2], "sniper_casing_%02d", i - 1);
				frame.push_back({ .cellName = casingCells[i - 2], .offset = {-68.0f, -40.0f} }); // TODO(미검증): 전 프레임 동일 오프셋, 탄피 궤적 확인 후 조정
			}

			throwFrames.push_back(std::move(frame));
		}
		baker.BakeAnimation(res, graphic, keyPrefix, { 140.0f, 230.0f }, throwFrames);
	};

	bakeSniperMonkey(L"sniper_grade1_baked", { {.cellName = "sniper_green_hat", .offset = {2.0f, 5.0f} } });
	bakeSniperMonkey(L"sniper_grade2_baked", { {.cellName = "sniper_full_metal_jacket", .offset = {2.0f, 5.0f} } });
	bakeSniperMonkey(L"sniper_grade3_baked", {
		{.cellName = "sniper_shades",            .offset = {2.0f, 12.0f} },
		{.cellName = "sniper_deadly_precision",  .offset = {2.0f, 5.0f} },
	});
	bakeSniperMonkey(L"sniper_grade4_baked", {
		{.cellName = "sniper_goggles",           .offset = {0.0f, -17.0f} },
		{.cellName = "sniper_faster_firing",  .offset = {2.0f, 5.0f} },
	});
	bakeSniperMonkey(L"sniper_grade5_baked", {
		{.cellName = "sniper_goggles",            .offset = {0.0f, -17.0f} },
		{.cellName = "sniper_cripple_moab",       .offset = {2.0f, 35.0f} },
	});


	// 폭탄타워: 등급마다 bomb_tower_XX 애니메이션이 재생되고, 마지막 프레임이 끝나면 발사된다(Tower::updateThrowAnimation).
	auto bakeBombTowerFrames = [&](const wchar_t* keyPrefix, D2D1_SIZE_F size, float wheelOffsetX,
		const char* bodyCellPrefix, D2D1_POINT_2F bodyOffset,
		const char* overlayCellPrefix, D2D1_POINT_2F overlayOffset)
		{
			std::vector<BakeFrame> frames;
			char bodyCells[4][32];
			char overlayCells[4][32]; // 루프 밖 선언 필수 — cellName은 포인터만 저장하므로 dangling 방지.

			for (int i = 1; i <= 4; ++i)
			{
				sprintf_s(bodyCells[i - 1], "%s_%02d", bodyCellPrefix, i);

				BakeFrame frame =
				{
					{ .cellName = "bomb_tower_wheel", .anchor = BakeAnchor::Left,  .offset = {-wheelOffsetX, 15.0f} },
					{ .cellName = "bomb_tower_wheel", .anchor = BakeAnchor::Right, .offset = { wheelOffsetX, 15.0f}, .flipX = true },
					{ .cellName = bodyCells[i - 1], .anchor = BakeAnchor::Left,  .offset = bodyOffset },
					{ .cellName = bodyCells[i - 1], .anchor = BakeAnchor::Right, .offset = bodyOffset, .flipX = true },
				};

				if (overlayCellPrefix != nullptr)
				{
					sprintf_s(overlayCells[i - 1], "%s_%02d", overlayCellPrefix, i);
					frame.push_back({ .cellName = overlayCells[i - 1], .anchor = BakeAnchor::Left,  .offset = overlayOffset });
					frame.push_back({ .cellName = overlayCells[i - 1], .anchor = BakeAnchor::Right, .offset = overlayOffset, .flipX = true });
				}

				frames.push_back(std::move(frame));
			}
			baker.BakeAnimation(res, graphic, keyPrefix, size, frames);
		};

	// 1등급: 문양 없는 기본형.
	bakeBombTowerFrames(L"bomb_tower_grade1_baked", { 200.0f, 150.0f }, 30.0f,
		"bomb_tower", { 0.0f, 0.0f }, nullptr, { 0.0f, 0.0f });
	// 2등급: frag 오버레이 추가.
	bakeBombTowerFrames(L"bomb_tower_grade2_baked", { 200.0f, 150.0f }, 30.0f,
		"bomb_tower", { 0.0f, 0.0f }, "bomb_tower_frag", { 0.0f, -10.0f });
	// 3등급: impact 셀 자체에 몸통이 포함되어 있어 베이스 오버레이 없이 단독 사용.
	bakeBombTowerFrames(L"bomb_tower_grade3_baked", { 200.0f, 150.0f }, 40.0f,
		"bomb_tower_impact", { 0.0f, 0.0f }, nullptr, { 0.0f, 0.0f });
	// 4등급: cluster 셀도 impact와 동일하게 단독 사용.
	bakeBombTowerFrames(L"bomb_tower_grade4_baked", { 200.0f, 150.0f }, 40.0f,
		"bomb_tower_cluster", { 0.0f, 0.0f }, nullptr, { 0.0f, 0.0f });

	// 5등급: idle엔 완전체 미사일을 들고 있다가, 발사가 시작되면 사일로 문이 01→06으로 열리며(문02~04에서 새
	// 미사일이 01→03으로 자라나고 문05부터 완전체로 바뀐 채 유지된다) 다시 06→01로 닫히고, 문이 완전히 닫힌
	// 시점(마지막 프레임이 끝나는 시점)에 그 완전체 미사일이 실제로 발사된다.
	// TODO(미검증): 실제 렌더링 확인 후 프레임 대응 관계 조정 필요.
	{
		baker.Bake(res, graphic, L"bomb_tower_grade5_baked_idle", { 200.0f, 180.0f }, {
			{ .cellName = "bomb_tower_wheel", .anchor = BakeAnchor::Left,  .offset = {-40.0f, 15.0f} },
			{ .cellName = "bomb_tower_wheel", .anchor = BakeAnchor::Right, .offset = { 40.0f, 15.0f}, .flipX = true },
			{ .cellName = "bomb_tower_silo",  .anchor = BakeAnchor::Left },
			{ .cellName = "bomb_tower_silo",  .anchor = BakeAnchor::Right, .flipX = true },
			{ .cellName = "bomb_tower_silo_doors_01", .anchor = BakeAnchor::Left },
			{ .cellName = "bomb_tower_silo_doors_01", .anchor = BakeAnchor::Right, .flipX = true },
			{ .cellName = "bomb_tower_missile_full" },
			});

		// 문 시퀀스: 01,02,03,04,05,06, 05,04,03,02,01 (열림 6 + 닫힘 5 = 11프레임)
		const int32 doorSeq[] = { 1,2,3,4,5,6,5,4,3,2,1 };
		std::vector<BakeFrame> silo5Frames;
		char doorCells[11][32];
		char missileCells[11][32];

		for (int32 i = 0; i < static_cast<int32>(std::size(doorSeq)); ++i)
		{
			sprintf_s(doorCells[i], "bomb_tower_silo_doors_%02d", doorSeq[i]);

			BakeFrame frame =
			{
				{ .cellName = "bomb_tower_wheel", .anchor = BakeAnchor::Left,  .offset = {-40.0f, 15.0f} },
				{ .cellName = "bomb_tower_wheel", .anchor = BakeAnchor::Right, .offset = { 40.0f, 15.0f}, .flipX = true },
				{ .cellName = "bomb_tower_silo",  .anchor = BakeAnchor::Left },
				{ .cellName = "bomb_tower_silo",  .anchor = BakeAnchor::Right, .flipX = true },
				{ .cellName = doorCells[i],       .anchor = BakeAnchor::Left },
				{ .cellName = doorCells[i],       .anchor = BakeAnchor::Right, .flipX = true },
			};

			// 문이 열리기 시작한 뒤(i>=1)부터 발사 직전(마지막 프레임)까지 새 미사일이 계속 보인다.
			// 문02~04(i=1~3)는 좌우 실로에서 함께 자라나는 missile_01~03(양쪽), 문05부터 닫힘 끝까지(i=4~10)는
			// 두 실로가 합쳐진 완전체 미사일 하나(중앙)로 유지된다.
			if (i >= 1)
			{
				if (i <= 3)
				{
					sprintf_s(missileCells[i], "bomb_tower_missile_%02d", i);
					frame.push_back({ .cellName = missileCells[i], .anchor = BakeAnchor::Left });
					frame.push_back({ .cellName = missileCells[i], .anchor = BakeAnchor::Right, .flipX = true });
				}
				else
				{
					frame.push_back({ .cellName = "bomb_tower_missile_full" });
				}
			}

			silo5Frames.push_back(std::move(frame));
		}
		baker.BakeAnimation(res, graphic, L"bomb_tower_grade5_baked", { 200.0f, 180.0f }, silo5Frames);
	}









	// plain_button(in_game_hud) 베이스 위에 try_again_icon(game_over_popup)을 겹쳐 하나의 이미지로 굽는다.
	// 서로 다른 아틀라스라 SpriteBaker(BakeFrame)로는 합성이 안 되어 BakeImage에 직접 그린다.
	{
		Image& hudImg = res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
		SpriteAtlas& hudAtlas = res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");
		Image& popupImg = res.GetImage(L"Resource\\Sprite\\game_over_popup.png");
		SpriteAtlas& popupAtlas = res.GetAtlas(L"Resource\\Sprite\\game_over_popup.xml");

		const CellInfo* baseCell = hudAtlas.GetCell("plain_button");
		const CellInfo* iconCell = popupAtlas.GetCell("try_again_icon");

		res.BakeImage(L"restart_button_baked", graphic, { 131.0f, 137.0f },
			[&](ID2D1RenderTarget* rt)
			{
				if (baseCell) hudImg.DrawSprite(rt, 65.5f, 68.5f, *baseCell, 1.0f, 0.0f);
				if (iconCell) popupImg.DrawSprite(rt, 65.5f, 68.5f, *iconCell, 1.0f, 0.0f);
			});
	}
}
