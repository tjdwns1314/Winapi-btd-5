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
	void Init(function<void()> onStartWave, function<void()> onShopClick,
		function<void()> onWaveUp, function<void()> onWaveDown);
	void Render(Graphic& graphic, bool isDraggingTower, const Vector& dragPreviewPos);
private:
	void renderDebugWaveButtons(Graphic& graphic) const;

	UIButton* _startButton = nullptr;
	UIButton* _dartMonkeyShopButton = nullptr;

	// 디버그용: 시작 라운드를 +/-로 조절하는 버튼(정식 스프라이트 없이 도형으로 그림).
	UIButton* _waveUpButton = nullptr;
	UIButton* _waveDownButton = nullptr;

	Image* _hudImg = nullptr;
	SpriteAtlas* _hudSprite = nullptr;
	Image* _inGameBg = nullptr;
	SpriteAtlas* _sprite = nullptr;
};
