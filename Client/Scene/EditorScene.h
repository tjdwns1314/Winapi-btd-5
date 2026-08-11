#pragma once

#include "Scene.h"

class Image;
class SpriteAtlas;

class EditorScene : public Scene
{
	using Super = Scene;

public :
	EditorScene() : Super(SceneType::Editor) {}
	virtual void Init(Graphic & graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic & graphic) override;

private :
	Image* _inGameBg = nullptr;
	SpriteAtlas* _sprite = nullptr;
};

