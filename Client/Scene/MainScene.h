#pragma once

#include "Scene.h"

class MainScene : public Scene
{
	using Super = Scene;

public:
	MainScene() : Super(SceneType::Main) {}

	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;
};

