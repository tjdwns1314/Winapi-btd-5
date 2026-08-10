#include "pch.h"
#include "GameSceneUI.h"
#include "UIManager.h"
#include "ResourceManager.h"

void GameSceneUI::Init(
	function<void()> onStartWave,
	function<void()> onDartShopClick,
	function<void()> onTackShopClick,
	function<void()> onWaveUp,
	function<void()> onWaveDown)
{
	ResourceManager& res = ResourceManager::GetInstance();
	_hudImg = &res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");
	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");

	_startButton = createButton(Vector(1575.0f, 450.0f), Vector(128.0f, 129.0f), onStartWave);
	_dartMonkeyShopButton = createButton(Vector(1575.0f, 650.0f), Vector(109.0f, 113.0f), onDartShopClick);
	_tackShooterShopButton = createButton(Vector(1575.0f, 790.0f), Vector(52.0f, 104.0f), onTackShopClick);
	_waveUpButton = createButton(Vector(1720.0f, 450.0f), Vector(40.0f, 40.0f), onWaveUp);
	_waveDownButton = createButton(Vector(1720.0f, 500.0f), Vector(40.0f, 40.0f), onWaveDown);
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

void GameSceneUI::Render(Graphic& graphic, const char* draggingTowerSprite, const Vector& dragPreviewPos)
{
	const CellInfo* playCell = _hudSprite->GetCell("play_icon");
	if (playCell != nullptr)
	{
		const Vector pos = _startButton->GetPos();
		_hudImg->DrawSprite(graphic, pos.x, pos.y, *playCell, 1.0f, 0.0f);
	}

	const CellInfo* bodyCell = _sprite->GetCell("dart_monkey_body");
	if (bodyCell != nullptr)
	{
		const Vector shopPos = _dartMonkeyShopButton->GetPos();
		_inGameBg->DrawSprite(graphic, shopPos.x, shopPos.y, *bodyCell, 1.0f, 0.0f);
	}

	const CellInfo* tackCell = _sprite->GetCell("tack_shooter_base");
	if (tackCell != nullptr)
	{
		// tack_shooter_base는 원의 절단면(대칭축)이 박스 오른쪽 끝(aw/2)에 있어서,
		// 두 장을 절단면 기준으로 shopPos에서 만나게 하려면 aw/2만큼 좌우로 밀어줘야 한다.
		const Vector shopPos = _tackShooterShopButton->GetPos();
		const float halfWidth = tackCell->aw * 0.5f;
		_inGameBg->DrawSprite(graphic, shopPos.x - halfWidth, shopPos.y, *tackCell, 1.0f, 0.0f);
		_inGameBg->DrawSprite(graphic, shopPos.x + halfWidth, shopPos.y, *tackCell, 1.0f, 0.0f, true);
	}

	if (draggingTowerSprite != nullptr)
	{
		const CellInfo* previewCell = _sprite->GetCell(draggingTowerSprite);
		if (previewCell != nullptr)
			_inGameBg->DrawSprite(graphic, dragPreviewPos.x, dragPreviewPos.y, *previewCell, 1.0f, 0.0f);
	}

	renderDebugWaveButtons(graphic);
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
		const D2D1_RECT_F rect = D2D1::RectF(pos.x, pos.y, pos.x + size.x, pos.y + size.y);

		ID2D1SolidColorBrush* bgBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::DarkGray, 0.8f));
		if (bgBrush != nullptr)
			renderTarget->FillRectangle(rect, bgBrush);

		const float cx = pos.x + size.x * 0.5f;
		const float cy = pos.y + size.y * 0.5f;
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
