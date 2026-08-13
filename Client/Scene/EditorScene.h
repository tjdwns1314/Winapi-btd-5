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

	Image* _hudImg = nullptr;      // in_game_hud.png
	SpriteAtlas * _hudSprite = nullptr; // in_game_hud.xml

	Image* _popupImg = nullptr;      // game_over_popup.png
	SpriteAtlas* _popupSprite = nullptr; // game_over_popup.xml
};

