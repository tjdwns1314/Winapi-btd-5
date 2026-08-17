#pragma once
#include "UIButton.h"
#include "TowerType.h"
#include "ObstacleType.h"

class Graphic;
class Image;
class SpriteAtlas;

// GameScene 전용 UI(시작 버튼, 상점 버튼, 타워 드래그 프리뷰)의
// 생성/배치/렌더링을 전담한다. GameScene은 콜백만 넘기고 결과를 그리게 시킨다.

struct TowerSelectionInfo
{
	bool isSelected = false;
	int32 grade = 1;
	int32 sellPrice = 0;
	int32 upgradePrice = 0;
	bool canUpgrade = false;
};

struct ObstacleSelectionInfo
{
	bool isSelected = false;
	int32 sellPrice = 0;
};



class GameSceneUI
{
public:
	void Init(
		function<void()> onStartWave,
		function<void()> onDartShopClick,
		function<void()> onTackShopClick,
		function<void()> onSniperShopClick,
		function<void()> onBombShopClick,
		function<void()> onObstacleShopClick,
		function<void()> onWaveUp,
		function<void()> onWaveDown,
		function<void()> onSellClick,
		function<void()> onUpgradeClick,
		function<void()> onObstacleSellClick,
		function<void()> onRestartClick);

	void Render(Graphic& graphic,
		bool isDraggingTower,
		TowerType draggingTowerType,
		bool isDraggingObstacle,
		const Vector& dragPreviewPos,
		const TowerSelectionInfo& selection,
		const ObstacleSelectionInfo& obstacleSelection,
		int32 hp,
		int32 gold, bool isWaveActive,
		bool isSpeedEnabled,
		bool isGameOver);
private:
	UIButton* createButton(const Vector& pos, const Vector& size, function<void()> onClick);

	// --------------------------------------------------
	//  HUD 배경 패널 / 골드·HP 텍스트
	// --------------------------------------------------
	void renderHudBackgroundPanel(Graphic& graphic) const;
	void renderGoldText(Graphic& graphic, int32 gold) const;
	void renderHpText(Graphic& graphic, int32 hp) const;

	// --------------------------------------------------
	//  웨이브 시작 / 디버그 웨이브 조절
	// --------------------------------------------------
	void renderStartButton(Graphic& graphic, bool isWaveActive, bool isSpeedEnabled)const;
	void renderDebugWaveButtons(Graphic& graphic) const;

	// --------------------------------------------------
	//  타워/장애물 상점
	// --------------------------------------------------
	void drawTowerIcon(Graphic& graphic, const Vector& pos, TowerType type, float scale) const;
	void renderTowerShopBoxes(Graphic& graphic) const;
	void drawObstacleIcon(Graphic& graphic, const Vector& pos, float scale) const;
	void drawRangePreview(Graphic& graphic, const Vector& pos, TowerType type) const;

	// --------------------------------------------------
	//  선택된 타워/장애물 패널 (판매/업그레이드)
	// --------------------------------------------------
	void renderTowerSelectionPanel(Graphic& graphic, const TowerSelectionInfo& selection) const;
	void renderObstacleSelectionPanel(Graphic& graphic, const ObstacleSelectionInfo& selection) const;

	// --------------------------------------------------
	//  게임오버 팝업
	// --------------------------------------------------
	void renderGameOverPopup(Graphic& graphic) const;

	// HUD 배경 패널 / 골드·HP 텍스트
	Image* _hudImg = nullptr;
	SpriteAtlas* _hudSprite = nullptr;

	// 웨이브 시작 / 디버그 웨이브 조절
	UIButton* _startButton = nullptr;
	UIButton* _waveUpButton = nullptr;   // 디버그용: 시작 라운드를 +/-로 조절(정식 스프라이트 없이 도형으로 그림)
	UIButton* _waveDownButton = nullptr;

	// 타워/장애물 상점
	Image* _inGameBg = nullptr;
	SpriteAtlas* _sprite = nullptr;
	UIButton* _dartMonkeyShopButton = nullptr;
	UIButton* _tackShooterShopButton = nullptr;
	UIButton* _sniperMonkeyShopButton = nullptr;
	UIButton* _bombTowerShopButton = nullptr;
	UIButton* _obstacleShopButton = nullptr;

	// 선택된 타워/장애물 패널 (판매/업그레이드)
	UIButton* _sellButton = nullptr;
	UIButton* _upgradeButton = nullptr;
	UIButton* _obstacleSellButton = nullptr;

	// 게임오버 팝업
	Image* _popupImg = nullptr;
	SpriteAtlas* _popupSprite = nullptr;
	UIButton* _restartButton = nullptr;
};
