#pragma once
#include "UIButton.h"
#include "TowerType.h"

class Graphic;
class Image;
class SpriteAtlas;

// GameScene 전용 UI(시작 버튼, 상점 버튼, 타워 드래그 프리뷰)의
// 생성/배치/렌더링을 전담한다. GameScene은 콜백만 넘기고 결과를 그리게 시킨다.
class GameSceneUI
{
public:
	void Init(
		function<void()> onStartWave,
		function<void()> onDartShopClick,
		function<void()> onTackShopClick,
		function<void()> onSniperShopClick,
		function<void()> onBombShopClick,
		function<void()> onWaveUp,
		function<void()> onWaveDown);
	void Render(Graphic& graphic,
		bool isDraggingTower,
		TowerType draggingTowerType,
		const Vector& dragPreviewPos,
		int32 hp,
		int32 gold);
private:
	UIButton* createButton(const Vector& pos, const Vector& size, function<void()> onClick);
	void renderDebugWaveButtons(Graphic& graphic) const;
	void renderGoldText(Graphic& graphic, int32 gold) const;
	void renderHpText(Graphic& graphic, int32 hp) const;
	void drawTowerIcon(Graphic& graphic, const Vector& pos, TowerType type, float scale) const;
	void drawRangePreview(Graphic& graphic, const Vector& pos, TowerType type) const;

	// 버튼
	UIButton* _startButton = nullptr;
	UIButton* _dartMonkeyShopButton = nullptr;
	UIButton* _tackShooterShopButton = nullptr;
	UIButton* _sniperMonkeyShopButton = nullptr;
	UIButton* _bombTowerShopButton = nullptr;
	UIButton* _waveUpButton = nullptr;   // 디버그용: 시작 라운드를 +/-로 조절(정식 스프라이트 없이 도형으로 그림)
	UIButton* _waveDownButton = nullptr;

	// 스프라이트 리소스
	Image* _hudImg = nullptr;
	SpriteAtlas* _hudSprite = nullptr;
	Image* _inGameBg = nullptr;
	SpriteAtlas* _sprite = nullptr;
};
