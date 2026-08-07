#include "pch.h"
#include "GameSceneUI.h"
#include "UIManager.h"
#include "ResourceManager.h"

void GameSceneUI::Init(function<void()> onStartWave, function<void()> onShopClick)
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
			_startButton->SetActive(false);
		});

	_dartMonkeyShopButton = new UIButton();
	_dartMonkeyShopButton->SetPos(Vector(1575.0f, 650.0f));
	_dartMonkeyShopButton->SetSize(Vector(109.0f, 113.0f));
	_dartMonkeyShopButton->SetActive(true);
	_dartMonkeyShopButton->SetOnClick(onShopClick);

	UIManager::GetInstance().Register(_startButton);
	UIManager::GetInstance().Register(_dartMonkeyShopButton);
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
	if (bodyCell == nullptr)
		return;

	const Vector shopPos = _dartMonkeyShopButton->GetPos();
	_inGameBg->DrawSprite(graphic, shopPos.x, shopPos.y, *bodyCell, 1.0f, 0.0f);

	if (isDraggingTower)
		_inGameBg->DrawSprite(graphic, dragPreviewPos.x, dragPreviewPos.y, *bodyCell, 1.0f, 0.0f);
}
