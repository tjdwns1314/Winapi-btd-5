#include "pch.h"
#include "GameSceneUI.h"
#include "UIManager.h"
#include "ResourceManager.h"

void GameSceneUI::Init(function<void()> onStartWave, function<void()> onShopClick,
	function<void()> onWaveUp, function<void()> onWaveDown)
{
	ResourceManager& res = ResourceManager::GetInstance();
	_hudImg = &res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");
	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");

	_startButton = new UIButton();
	_startButton->SetPos(Vector(1575.0f, 450.0f));
	_startButton->SetSize(Vector(128.0f, 129.0f));
	_startButton->SetActive(true);
	_startButton->SetOnClick([this, onStartWave]()
		{
			onStartWave();
		});

	_dartMonkeyShopButton = new UIButton();
	_dartMonkeyShopButton->SetPos(Vector(1575.0f, 650.0f));
	_dartMonkeyShopButton->SetSize(Vector(109.0f, 113.0f));
	_dartMonkeyShopButton->SetActive(true);
	_dartMonkeyShopButton->SetOnClick(onShopClick);

	_waveUpButton = new UIButton();
	_waveUpButton->SetPos(Vector(1720.0f, 450.0f));
	_waveUpButton->SetSize(Vector(40.0f, 40.0f));
	_waveUpButton->SetActive(true);
	_waveUpButton->SetOnClick(onWaveUp);

	_waveDownButton = new UIButton();
	_waveDownButton->SetPos(Vector(1720.0f, 500.0f));
	_waveDownButton->SetSize(Vector(40.0f, 40.0f));
	_waveDownButton->SetActive(true);
	_waveDownButton->SetOnClick(onWaveDown);

	UIManager::GetInstance().Register(_startButton);
	UIManager::GetInstance().Register(_dartMonkeyShopButton);
	UIManager::GetInstance().Register(_waveUpButton);
	UIManager::GetInstance().Register(_waveDownButton);
}

void GameSceneUI::Render(Graphic& graphic, bool isDraggingTower, const Vector& dragPreviewPos)
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

		if (isDraggingTower)
			_inGameBg->DrawSprite(graphic, dragPreviewPos.x, dragPreviewPos.y, *bodyCell, 1.0f, 0.0f);
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
