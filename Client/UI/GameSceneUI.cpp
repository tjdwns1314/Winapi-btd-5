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
	function<void()> onWaveUp,
	function<void()> onWaveDown,
	function<void()> onSellClick,
	function<void()> onUpgradeClick)
{
	ResourceManager& res = ResourceManager::GetInstance();
	_hudImg = &res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");
	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");

	_startButton = createButton(Vector(1512.5f, 950.0f), Vector(128.0f, 129.0f), onStartWave);
	_dartMonkeyShopButton = createButton(Vector(1512.5f, 350.0f), Vector(109.0f, 113.0f), onDartShopClick);
	_tackShooterShopButton = createButton(Vector(1675.0f, 350.0f), Vector(52.0f, 104.0f), onTackShopClick);
	_sniperMonkeyShopButton = createButton(Vector(1512.5f, 550.0f), Vector(109.0f, 113.0f), onSniperShopClick);
	_bombTowerShopButton = createButton(Vector(1675.0f, 550.0f), Vector(109.0f, 113.0f), onBombShopClick);
	_waveUpButton = createButton(Vector(1720.0f, 950.0f), Vector(40.0f, 40.0f), onWaveUp);
	_waveDownButton = createButton(Vector(1720.0f, 900.0f), Vector(40.0f, 40.0f), onWaveDown);

	// 타워 선택 패널: 상점 버튼(y=550)과 웨이브 버튼(y=900) 사이 빈 공간에 고정 배치.
	// 위치/크기는 임시값 — 빌드 후 눈으로 보고 조정할 것.
	_sellButton = createButton(Vector(1512.5f, 700.0f), Vector(109.0f, 60.0f), onSellClick);
	_upgradeButton = createButton(Vector(1675.0f, 700.0f), Vector(109.0f, 60.0f), onUpgradeClick);
	_sellButton->SetActive(false);
	_upgradeButton->SetActive(false);
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

void GameSceneUI::Render(Graphic& graphic, bool isDraggingTower, TowerType draggingTowerType,
	const Vector& dragPreviewPos, const TowerSelectionInfo& selection, int32 hp, int32 gold, bool isWaveActive, bool isSpeedEnabled)
{
	renderStartButton(graphic, isWaveActive, isSpeedEnabled);

	drawTowerIcon(graphic, _dartMonkeyShopButton->GetPos(), TowerType::DartMonkey, 1.0f);
	// 상점 박스가 작아서(52x104) 베이크 텍스처(200x200)를 그대로 넣을 수 없어 축소해서 그린다.
	// 0.5는 임시값 — 빌드 후 눈으로 보고 조정할 것.
	drawTowerIcon(graphic, _tackShooterShopButton->GetPos(), TowerType::TackShooter, 1.0f);
	drawTowerIcon(graphic, _sniperMonkeyShopButton->GetPos(), TowerType::SniperMonkey, 1.0f);
	drawTowerIcon(graphic, _bombTowerShopButton->GetPos(), TowerType::BombTower, 1.0f);

	if (isDraggingTower)
	{
		drawRangePreview(graphic, dragPreviewPos, draggingTowerType);
		drawTowerIcon(graphic, dragPreviewPos, draggingTowerType, 1.0f);
	}

	renderDebugWaveButtons(graphic);
	renderGoldText(graphic, gold);
	renderHpText(graphic, hp);

	_sellButton->SetActive(selection.isSelected);
	_upgradeButton->SetActive(selection.isSelected && selection.canUpgrade);
	if (selection.isSelected)
		renderTowerSelectionPanel(graphic, selection);
}

void GameSceneUI::drawRangePreview(Graphic& graphic, const Vector& pos, TowerType type) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::White, 0.5f));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	const float range = GetTowerStat(type).attackRange;
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), range, range), brush, 2.f);
}

void GameSceneUI::drawTowerIcon(Graphic& graphic, const Vector& pos, TowerType type, float scale) const
{
	const TowerVisual& visual = GetTowerVisual(type);
	if (visual.useBakedImage)
	{
		ResourceManager::GetInstance().GetImage(visual.bakedImageKey.c_str()).Draw(graphic, pos.x, pos.y, scale, 0.0f);
		return;
	}

	if (const CellInfo* cell = _sprite->GetCell(visual.cellName.c_str()))
		_inGameBg->DrawSprite(graphic, pos.x, pos.y, *cell, scale, 0.0f);
}

void GameSceneUI::renderGoldText(Graphic& graphic, int32 gold) const
{
	wchar_t text[32];
	swprintf_s(text, L"Gold: %d", gold);

	graphic.DrawTextW(text, D2D1::RectF(1440.0f, 20.0f, 1760.0f, 60.0f),
		FONT_30, D2D1::ColorF(D2D1::ColorF::Gold), DWRITE_TEXT_ALIGNMENT_CENTER);
}

void GameSceneUI::renderHpText(Graphic& graphic, int32 hp) const
{
	wchar_t text[32];
	swprintf_s(text, L"HP: %d", hp);

	graphic.DrawTextW(text, D2D1::RectF(1440.0f, 60.0f, 1760.0f, 100.0f),
		FONT_30, D2D1::ColorF(D2D1::ColorF::Red), DWRITE_TEXT_ALIGNMENT_CENTER);
}

void GameSceneUI::renderTowerSelectionPanel(Graphic& graphic, const TowerSelectionInfo& selection) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* bgBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::DarkSlateGray, 0.85f));

	auto drawButtonBg = [&](UIButton* button)
	{
		if (renderTarget == nullptr || bgBrush == nullptr)
			return;
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
		graphic.DrawTextW(text, D2D1::RectF(
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
