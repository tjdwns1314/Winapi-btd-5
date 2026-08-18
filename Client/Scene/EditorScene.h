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

	Image* _upgradeIconsImg = nullptr;      // upgrade_icons.png
	SpriteAtlas* _upgradeIconsSprite = nullptr; // upgrade_icons.xml

	Image* _sharedSheetImg = nullptr;      // shared_sheet.png
	SpriteAtlas* _sharedSheetSprite = nullptr; // shared_sheet.xml

	// Resource/Sprite/nukki/ 개별 아이콘(아틀라스 없이 낱개 PNG)
	Image* _nukkiAutoplayImg = nullptr;
	Image* _nukkiMusicImg = nullptr;
	Image* _nukkiReplayImg = nullptr;
	Image* _nukkiResumeImg = nullptr;
	Image* _nukkiSfxImg = nullptr;
	Image* _nukkiXImg = nullptr;
	Image* _nukkiCircleImg = nullptr;
	Image* _nukkiTwoCircleImg = nullptr;
	Image* _nukkiSmallCircleImg = nullptr;
	Image* _nukkiCogwheelImg = nullptr;

	Image* _loadingScreenImg = nullptr;      // loading_screen.png
	SpriteAtlas* _loadingScreenSprite = nullptr; // loading_screen.xml
};

