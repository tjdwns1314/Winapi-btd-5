#pragma once
#include "Scene.h"
#include "Image.h"
#include "Sprite.h"

class GameScene : public Scene
{
	using Super = Scene;

public :
	GameScene() : Super(SceneType::Game) {}

	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;

private :
	Image _inGameBg;
	Sprite _sprite;
};

