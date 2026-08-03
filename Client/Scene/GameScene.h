#pragma once
#include "Scene.h"
#include "Image.h"
#include "Sprite.h"
#include "Grid.h"

class GameScene : public Scene
{
	using Super = Scene;

public :
	GameScene() : Super(SceneType::Game) {}

	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;



private:
	void renderGrid(Graphic& graphic);

	Image _inGameBg;
	Image _monkeyLaneBg;      // 기존 _RealGameBG 대체
	Image _bloonImg;
	Sprite _sprite;           // InGame.xml
	Sprite _monkeyLaneSprite; // monkey_lane.xml
	Grid _grid;

};

