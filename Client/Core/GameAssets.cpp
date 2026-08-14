#include "pch.h"
#include "GameAssets.h"
#include "ResourceManager.h"
#include "SpriteBaker.h"

void GameAssets::Load(Graphic& graphic)
{
	ResourceManager& res = ResourceManager::GetInstance();

	res.LoadImage(graphic, L"Resource\\Sprite\\monkey_lane.png");
	res.LoadAtlas(L"Resource\\Sprite\\monkey_lane.xml");

	res.LoadImage(graphic, L"Resource\\Sprite\\InGame.png");
	res.LoadAtlas(L"Resource\\Sprite\\InGame.xml");

	res.LoadImage(graphic, L"Resource\\Tile\\Tile1.png");
	res.LoadImage(graphic, L"Resource\\Tile\\Tile2.png");

	res.LoadImage(graphic, L"Resource\\Sprite\\in_game_hud.png");
	res.LoadAtlas(L"Resource\\Sprite\\in_game_hud.xml");

	res.LoadImage(graphic, L"Resource\\Sprite\\game_over_popup.png");
	res.LoadAtlas(L"Resource\\Sprite\\game_over_popup.xml");

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

	baker.Bake(res, graphic, L"tack_shooter_baked", { 200.0f, 200.0f }, {
		{ .cellName = "tack_shooter_firing_01", .anchor = BakeAnchor::TopLeft },
		{ .cellName = "tack_shooter_firing_01", .anchor = BakeAnchor::TopRight,    .flipX = true },
		{ .cellName = "tack_shooter_firing_01", .anchor = BakeAnchor::BottomLeft,  .angle = 180.0f, .flipX = true },
		{ .cellName = "tack_shooter_firing_01", .anchor = BakeAnchor::BottomRight, .angle = 180.0f },
		{ .cellName = "tack_shooter_base",      .anchor = BakeAnchor::Left },
		{ .cellName = "tack_shooter_base",      .anchor = BakeAnchor::Right,       .flipX = true },
		{ .cellName = "tack_shooter_tack_logo", .anchor = BakeAnchor::Left },
		{ .cellName = "tack_shooter_tack_logo", .anchor = BakeAnchor::Right,       .flipX = true },
	});

	baker.Bake(res, graphic, L"bomb_tower_baked", { 200.0f, 150.0f }, {
		{.cellName = "bomb_tower_wheel", .anchor = BakeAnchor::Left,  .offset = {-30.0f, 15.0f} },
		{.cellName = "bomb_tower_wheel", .anchor = BakeAnchor::Right, .offset = { 30.0f, 15.0f}, .flipX = true },
		{ .cellName = "bomb_tower_01", .anchor = BakeAnchor::Left },
		{ .cellName = "bomb_tower_01", .anchor = BakeAnchor::Right, .flipX = true },
	});

	//	baker.Bake(res, graphic, L"dart_monkey_baked", { 125.0f, 140.0f }, {
	//{.cellName = "dart_monkey_arm_01",.offset = {2.0f,0.0f} },
	//{.cellName = "dart_monkey_body",.offset = {7.5f,10.0f} },
	//{.cellName = "red_bandana",.offset = {0.0f,-11.0f}},
	//		});

//	baker.Bake(res, graphic, L"dart_monkey_baked", { 125.0f, 140.0f }, {
//{.cellName = "dart_monkey_arm_01",.offset = {2.0f,0.0f} },
//{.cellName = "dart_monkey_body",.offset = {7.5f,10.0f} },
//{.cellName = "triple_darts_bandana",.offset = {-9.5f,10.0f}},
//		});



		
		auto bakeDartMonkeyThrow = [&](const wchar_t* keyPrefix, const char* bandanaCell, D2D1_POINT_2F bandanaOffset = { 0.0f, 0.0f })
		{
			std::vector<BakeFrame> frames;
			for (int i = 1; i <= 3; ++i)
			{
				char armCell[32];
				sprintf_s(armCell, "dart_monkey_arm_%02d", i);

				BakeFrame frame = 
				{
				{.cellName = "dart_monkey_body",.offset = {7.5f,10.0f} },
				{.cellName = armCell,.offset = {2.0f,0.0f} },
				};
				if (bandanaCell != nullptr)
						
				frame.push_back({ .cellName = bandanaCell,.offset = bandanaOffset });

				frames.push_back(std::move(frame));
				}
			
				baker.BakeAnimation(res, graphic, keyPrefix, { 125.0f, 140.0f }, frames);
			};

		bakeDartMonkeyThrow(L"dart_monkey_base_baked", nullptr);
		bakeDartMonkeyThrow(L"dart_monkey_red_baked", "red_bandana", { 0.0f, -11.0f });
		bakeDartMonkeyThrow(L"dart_monkey_blue_baked", "blue_bandana", { 0.0f, -11.0f });
		bakeDartMonkeyThrow(L"dart_monkey_green_baked", "green_bandana", { 0.0f, -11.0f });
		bakeDartMonkeyThrow(L"dart_monkey_triple_baked", "triple_darts_bandana", { -9.5f, 10.0f });











	baker.Bake(res, graphic, L"sniper_monkey_baked", { 140.0f, 230.0f }, {
	{.cellName = "sniper_arm",         .offset = {-5.0f, -60.0f} },
	{.cellName = "dart_monkey_body" },
	{.cellName = "sniper_green_hat",   .offset = {-5.0f, -5.0f} },
	{.cellName = "sniper_basic_rifle", .offset = {-25.0f, -70.0f} },
	});

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
