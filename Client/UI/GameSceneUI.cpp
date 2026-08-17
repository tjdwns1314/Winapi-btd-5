#include "pch.h"
#include "GameSceneUI.h"
#include "UIManager.h"
#include "ResourceManager.h"

void GameSceneUI::Init(
	function<void()> onStartWave,
	function<void()> onDartShopClick,
	function<void()> onTackShopClick,
	function<void()> onSniperShopClick,
	function<void()> onBombShopClick,
	function<void()> onObstacleShopClick,
	function<void()> onWaveUp,
	function<void()> onWaveDown,
	function<void()> onSellClick,
	function<void()> onUpgradeClick,
	function<void()> onObstacleSellClick,
	function<void()> onRestartClick)
{
	ResourceManager& res = ResourceManager::GetInstance();
	// HUD 배경 패널
	_hudImg = &res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");
	// 타워/장애물 상점 아이콘
	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");
	// 게임오버 팝업
	_popupImg = &res.GetImage(L"Resource\\Sprite\\game_over_popup.png");
	_popupSprite = &res.GetAtlas(L"Resource\\Sprite\\game_over_popup.xml");

	// 웨이브 시작 버튼
	_startButton = createButton(Vector(1512.5f, 950.0f), Vector(128.0f, 129.0f), onStartWave);

	// 타워 상점 버튼: 스크롤 패널(y=270~518) 안에 2x2 그리드로 배치.
	// 클릭 판정 크기는 실제로 그려지는 tower_thumbs_box 배경(113x93, renderTowerShopBoxes 참고)과 맞춘다.
	_dartMonkeyShopButton = createButton(Vector(1520.0f, 332.0f), Vector(113.0f, 93.0f), onDartShopClick);
	_tackShooterShopButton = createButton(Vector(1680.0f, 332.0f), Vector(113.0f, 93.0f), onTackShopClick);
	_sniperMonkeyShopButton = createButton(Vector(1520.0f, 456.0f), Vector(113.0f, 93.0f), onSniperShopClick);
	_bombTowerShopButton = createButton(Vector(1680.0f, 456.0f), Vector(113.0f, 93.0f), onBombShopClick);
	// 위치는 임시값 — 빌드 후 눈으로 보고 조정할 것.
	_obstacleShopButton = createButton(Vector(1675.0f, 900.0f), Vector(109.0f, 113.0f), onObstacleShopClick);

	// 디버그 웨이브 +/- 버튼
	_waveUpButton = createButton(Vector(1720.0f, 950.0f), Vector(40.0f, 40.0f), onWaveUp);
	_waveDownButton = createButton(Vector(1720.0f, 900.0f), Vector(40.0f, 40.0f), onWaveDown);

	// 타워 선택 패널: 상점 버튼(y=550)과 웨이브 버튼(y=900) 사이 빈 공간에 고정 배치.
	// 위치/크기는 임시값 — 빌드 후 눈으로 보고 조정할 것.
	_sellButton = createButton(Vector(1512.5f, 800.0f), Vector(109.0f, 60.0f), onSellClick);
	_upgradeButton = createButton(Vector(1675.0f, 800.0f), Vector(109.0f, 60.0f), onUpgradeClick);
	_sellButton->SetActive(false);
	_upgradeButton->SetActive(false);

	_obstacleSellButton = createButton(Vector(1837.5f, 800.0f), Vector(109.0f, 60.0f), onObstacleSellClick);
	_obstacleSellButton->SetActive(false);

	// 게임오버 팝업의 재시작 버튼. baked 이미지(131x137) 크기에 맞춰 게임 영역 정중앙에 둔다.
	_restartButton = createButton(Vector(GameAreaCenterX, GameAreaCenterY), Vector(131.0f, 137.0f), onRestartClick);
	_restartButton->SetActive(false);
}

UIButton* GameSceneUI::createButton(const Vector& pos, const Vector& size, function<void()> onClick)
{
	UIButton* button = new UIButton();
	button->SetPos(pos);
	button->SetSize(size);
	button->SetActive(true);
	button->SetOnClick(onClick);
	UIManager::GetInstance().Register(button);
	return button;
}

void GameSceneUI::Render(Graphic& graphic, bool isDraggingTower, TowerType draggingTowerType,
	bool isDraggingObstacle,
	const Vector& dragPreviewPos, const TowerSelectionInfo& selection,
	const ObstacleSelectionInfo& obstacleSelection,
	int32 hp, int32 gold, bool isWaveActive, bool isSpeedEnabled,
	bool isGameOver)
{
	renderHudBackgroundPanel(graphic);

	renderStartButton(graphic, isWaveActive, isSpeedEnabled);

	renderTowerShopBoxes(graphic);

	if (_dartMonkeyShopButton != nullptr) drawTowerIcon(graphic, _dartMonkeyShopButton->GetPos(), TowerType::DartMonkey, 0.7f);
	if (_tackShooterShopButton != nullptr) drawTowerIcon(graphic, _tackShooterShopButton->GetPos(), TowerType::TackShooter, 0.7f);
	if (_sniperMonkeyShopButton != nullptr) drawTowerIcon(graphic, _sniperMonkeyShopButton->GetPos(), TowerType::SniperMonkey, 0.7f);
	if (_bombTowerShopButton != nullptr) drawTowerIcon(graphic, _bombTowerShopButton->GetPos(), TowerType::BombTower, 0.7f);
	if (_obstacleShopButton != nullptr) drawObstacleIcon(graphic, _obstacleShopButton->GetPos(), 1.0f);

	if (isDraggingTower)
	{
		drawRangePreview(graphic, dragPreviewPos, draggingTowerType);
		drawTowerIcon(graphic, dragPreviewPos, draggingTowerType, 0.7f);
	}
	if (isDraggingObstacle)
		drawObstacleIcon(graphic, dragPreviewPos, 1.0f);

	renderDebugWaveButtons(graphic);
	renderGoldText(graphic, gold);
	renderHpText(graphic, hp);

	if (_sellButton != nullptr) _sellButton->SetActive(selection.isSelected);
	if (_upgradeButton != nullptr) _upgradeButton->SetActive(selection.isSelected && selection.canUpgrade);
	if (selection.isSelected)
		renderTowerSelectionPanel(graphic, selection);

	if (_obstacleSellButton != nullptr) _obstacleSellButton->SetActive(obstacleSelection.isSelected);
	if (obstacleSelection.isSelected)
		renderObstacleSelectionPanel(graphic, obstacleSelection);

	if (_restartButton != nullptr) _restartButton->SetActive(isGameOver);
	if (isGameOver)
		renderGameOverPopup(graphic);
}

// --------------------------------------------------
//  HUD 배경 패널 / 골드·HP 텍스트
// --------------------------------------------------

// 오른쪽 UI 영역(전체 가로 - 게임 영역)에 정확히 맞춰 가로폭을 늘려서 그린다.
void GameSceneUI::renderHudBackgroundPanel(Graphic& graphic) const
{
	constexpr float kUiPanelWidth = static_cast<float>(GWinSizeX - GameAreaWidth);
	const float centerX = static_cast<float>(GameAreaWidth) + kUiPanelWidth * 0.5f;

	// 1. 상단 배경(side_hud_bg_01, 높이 270)
	if (const CellInfo* cell = _hudSprite->GetCell("side_hud_bg_01"))
	{
		constexpr float kPanelCenterY = 135.0f;
		const float scaleX = kUiPanelWidth / cell->aw;
		_hudImg->DrawSprite(graphic, centerX, kPanelCenterY, *cell, scaleX, 0.0f, false, 1.0f);
	}

	// 2. 그 아래 이어지는 스크롤 배경(side_hud_scroll, 높이 248)
	if (const CellInfo* cell = _hudSprite->GetCell("side_hud_scroll"))
	{
		constexpr float kScrollCenterY = 270.0f + 248.0f * 0.5f; // 상단 배경 높이(270) + 이 패널 높이(248)/2
		const float scaleX = kUiPanelWidth / cell->aw;
		_hudImg->DrawSprite(graphic, centerX, kScrollCenterY, *cell, scaleX, 0.0f, false, 1.0f);
	}
}

void GameSceneUI::renderGoldText(Graphic& graphic, int32 gold) const
{
	wchar_t text[32];
	swprintf_s(text, L"Gold: %d", gold);

	graphic.DrawString(text, D2D1::RectF(1440.0f, 20.0f, 1760.0f, 60.0f),
		FONT_30, D2D1::ColorF(D2D1::ColorF::Gold), DWRITE_TEXT_ALIGNMENT_CENTER);
}

void GameSceneUI::renderHpText(Graphic& graphic, int32 hp) const
{
	wchar_t text[32];
	swprintf_s(text, L"HP: %d", hp);

	graphic.DrawString(text, D2D1::RectF(1440.0f, 60.0f, 1760.0f, 100.0f),
		FONT_30, D2D1::ColorF(D2D1::ColorF::Red), DWRITE_TEXT_ALIGNMENT_CENTER);
}

// --------------------------------------------------
//  웨이브 시작 / 디버그 웨이브 조절
// --------------------------------------------------

void GameSceneUI::renderStartButton(Graphic& graphic, bool isWaveActive, bool isSpeedEnabled) const
{
	const char* cellName = "play_icon";
	if (isWaveActive)
		cellName = isSpeedEnabled ? "ff_icon_red" : "ff_icon";

	const CellInfo* cell = _hudSprite->GetCell(cellName);
	if (cell == nullptr) return;

	const Vector pos = _startButton->GetPos();
	_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, 1.0f, 0.0f);
}

void GameSceneUI::renderDebugWaveButtons(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	if (renderTarget == nullptr)
		return;

	auto drawButton = [&](UIButton* button, bool isPlus)
	{
		if (button == nullptr)
			return;

		const Vector pos = button->GetPos();
		const Vector size = button->GetSize();
		const D2D1_RECT_F rect = D2D1::RectF(
			pos.x - size.x * 0.5f,
			pos.y - size.y * 0.5f,
			pos.x + size.x * 0.5f,
			pos.y + size.y * 0.5f);

		ID2D1SolidColorBrush* bgBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::DarkGray, 0.8f));
		if (bgBrush != nullptr)
			renderTarget->FillRectangle(rect, bgBrush);

		const float cx = pos.x;
		const float cy = pos.y;
		const float half = size.x * 0.3f;
		const float thickness = 4.0f;

		ID2D1SolidColorBrush* markBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::White));
		if (markBrush == nullptr)
			return;

		renderTarget->FillRectangle(
			D2D1::RectF(cx - half, cy - thickness * 0.5f, cx + half, cy + thickness * 0.5f), markBrush);

		if (isPlus)
		{
			renderTarget->FillRectangle(
				D2D1::RectF(cx - thickness * 0.5f, cy - half, cx + thickness * 0.5f, cy + half), markBrush);
		}
	};

	drawButton(_waveUpButton, true);
	drawButton(_waveDownButton, false);
}

// --------------------------------------------------
//  타워/장애물 상점
// --------------------------------------------------

void GameSceneUI::drawTowerIcon(Graphic& graphic, const Vector& pos, TowerType type, float scale) const
{
	const TowerVisual& visual = GetTowerVisual(type);

	if (visual.useBakedImage)
	{
		ResourceManager::GetInstance().GetImage(visual.bakedImageKey.c_str()).Draw(graphic, pos.x, pos.y, scale, 0.0f);
		return;
	}

	if (_sprite != nullptr && _inGameBg != nullptr)
	{
		if (const CellInfo* cell = _sprite->GetCell(visual.cellName.c_str()))
			_inGameBg->DrawSprite(graphic, pos.x, pos.y, *cell, scale, 0.0f);
	}
}

// 타워 상점 버튼 4개 자리에 tower_thumbs_box 배경을 2x2로 깔아준다(아이콘보다 먼저 그려야 함).
void GameSceneUI::renderTowerShopBoxes(Graphic& graphic) const
{
	const CellInfo* cell = _hudSprite->GetCell("tower_thumbs_box");
	if (cell == nullptr)
		return;

	auto drawBox = [&](UIButton* button)
	{
		if (button == nullptr)
			return;
		const Vector pos = button->GetPos();
		_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, 1.0f, 0.0f);
	};

	drawBox(_dartMonkeyShopButton);
	drawBox(_tackShooterShopButton);
	drawBox(_sniperMonkeyShopButton);
	drawBox(_bombTowerShopButton);
}

void GameSceneUI::drawObstacleIcon(Graphic& graphic, const Vector& pos, float scale) const
{
	if (_sprite == nullptr || _inGameBg == nullptr)
		return;

	const ObstacleStat& stat = GetObstacleStat(ObstacleType::BananaFarmTree);
	if (const CellInfo* cell = _sprite->GetCell(stat.cellName.c_str()))
		_inGameBg->DrawSprite(graphic, pos.x, pos.y, *cell, scale, 0.0f);
}

void GameSceneUI::drawRangePreview(Graphic& graphic, const Vector& pos, TowerType type) const
{
	if (type == TowerType::SniperMonkey)
		return;

	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Black, 0.35f));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	const float range = GetTowerStat(type).grades.front().attackRange;
	renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), range, range), brush);
}

// --------------------------------------------------
//  선택된 타워/장애물 패널 (판매/업그레이드)
// --------------------------------------------------

void GameSceneUI::renderTowerSelectionPanel(Graphic& graphic, const TowerSelectionInfo& selection) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();

	auto drawButtonBg = [&](UIButton* button)
	{
			if (renderTarget == nullptr)
			return;
			ID2D1SolidColorBrush* bgBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::DarkSlateGray, 0.85f));
		const Vector pos = button->GetPos();
		const Vector size = button->GetSize();
		renderTarget->FillRectangle(D2D1::RectF(
			pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
			pos.x + size.x * 0.5f, pos.y + size.y * 0.5f), bgBrush);
	};

	auto drawPriceText = [&](UIButton* button, const wchar_t* text)
	{
		const Vector pos = button->GetPos();
		const Vector size = button->GetSize();
		graphic.DrawString(text, D2D1::RectF(
			pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
			pos.x + size.x * 0.5f, pos.y + size.y * 0.5f),
			FONT_20, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER);
	};

	drawButtonBg(_sellButton);
	wchar_t sellText[32];
	swprintf_s(sellText, L"판매: %d", selection.sellPrice);
	drawPriceText(_sellButton, sellText);

	if (selection.canUpgrade)
	{
		drawButtonBg(_upgradeButton);
		wchar_t upgradeText[32];
		swprintf_s(upgradeText, L"업그레이드: %d", selection.upgradePrice);
		drawPriceText(_upgradeButton, upgradeText);
	}

	// 배경 브러시(bgBrush)를 다 쓴 뒤 맨 마지막에 그린다 — 그 전에 그리면
	// 공용 브러시 색이 White로 바뀌어서 sell/upgrade 배경이 흰색으로 칠해지는 버그가 생긴다.
	graphic.DrawString(selection.name, D2D1::RectF(1450.0f, 560.0f, 1740.0f, 600.0f),
		FONT_20, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER);

	wchar_t levelText[32];
	swprintf_s(levelText, L"레벨 %d", selection.grade);
	graphic.DrawString(levelText, D2D1::RectF(1450.0f, 600.0f, 1740.0f, 800.0f),
		FONT_20, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER);
}

void GameSceneUI::renderObstacleSelectionPanel(Graphic& graphic, const ObstacleSelectionInfo& selection) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	if (renderTarget == nullptr)
		return;

	ID2D1SolidColorBrush* bgBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::DarkSlateGray, 0.85f));
	const Vector pos = _obstacleSellButton->GetPos();
	const Vector size = _obstacleSellButton->GetSize();
	if (bgBrush != nullptr)
	{
		renderTarget->FillRectangle(D2D1::RectF(
			pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
			pos.x + size.x * 0.5f, pos.y + size.y * 0.5f), bgBrush);
	}

	wchar_t sellText[32];
	swprintf_s(sellText, L"판매: %d", selection.sellPrice);
	graphic.DrawString(sellText, D2D1::RectF(
		pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
		pos.x + size.x * 0.5f, pos.y + size.y * 0.5f),
		FONT_20, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER);
}

// --------------------------------------------------
//  게임오버 팝업
// --------------------------------------------------

void GameSceneUI::renderGameOverPopup(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* dimBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Black, 0.6f));
	if (renderTarget != nullptr && dimBrush != nullptr)
	{
		// game_over_popup.xml에는 배경 패널 셀이 없어서, 게임 영역 전체를 어둡게 깔아 팝업처럼 보이게 한다.
		renderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f,
			static_cast<float>(GameAreaWidth), static_cast<float>(GameAreaHeight)), dimBrush);
	}

	graphic.DrawString(L"GAME OVER",
		D2D1::RectF(0.0f, GameAreaCenterY - 160.0f, static_cast<float>(GameAreaWidth), GameAreaCenterY - 80.0f),
		FONT_30, D2D1::ColorF(D2D1::ColorF::Red), DWRITE_TEXT_ALIGNMENT_CENTER);

	ResourceManager::GetInstance().GetImage(L"restart_button_baked")
		.Draw(graphic, GameAreaCenterX, GameAreaCenterY, 1.0f, 0.0f);
}
