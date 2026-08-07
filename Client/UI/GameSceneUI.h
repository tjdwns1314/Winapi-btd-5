#pragma once
#include "UIButton.h"

class Graphic;
class Image;
class SpriteAtlas;

// GameScene 전용 UI(시작 버튼, 상점 버튼, 타워 드래그 프리뷰)의
// 생성/배치/렌더링을 전담한다. GameScene은 콜백만 넘기고 결과를 그리게 시킨다.
class GameSceneUI
{
public:
	void Init(function<void()> onStartWave, function<void()> onShopClick);
	void Render(Graphic& graphic, bool isDraggingTower, const Vector& dragPreviewPos);

private:
	UIButton* _startButton = nullptr;
	UIButton* _dartMonkeyShopButton = nullptr;

	Image* _hudImg = nullptr;
	SpriteAtlas* _hudSprite = nullptr;
	Image* _inGameBg = nullptr;
	SpriteAtlas* _sprite = nullptr;
};
