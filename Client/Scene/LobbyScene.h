#pragma once
#include "Scene.h"

class LobbyScene : public Scene
{
	using Super = Scene;

public :
	LobbyScene() : Super(SceneType::Lobby) {}

	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;
};
