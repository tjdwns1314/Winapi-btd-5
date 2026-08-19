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
	const wchar_t* name = L"";
	int32 grade = 1;
	int32 sellPrice = 0;
	int32 upgradePrice = 0;
	bool canUpgrade = false;
	string upgradeIconKey;
	string avatarKey;
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
		function<void()> onRestartClick,
		function<void()> onSettingsClick,
		function<void()> onSettingsCloseClick);

	void Render(Graphic& graphic,
		bool isDraggingTower,
		TowerType draggingTowerType,
		bool isDraggingObstacle,
		const Vector& dragPreviewPos,
		const TowerSelectionInfo& selection,
		const ObstacleSelectionInfo& obstacleSelection,
		int32 hp,
		int32 gold, bool isWaveActive,
		int32 currentRound, int32 totalRound,
		bool isSpeedEnabled,
		bool isGameOver);

	// 설정 팝업 전용. 다른 모든 그리기(액터, HUD, 다른 팝업)가 끝난 뒤 프레임 맨 마지막에 호출해야
	// 액터/버튼에 가려지지 않고 항상 최상단에 딤+버튼이 그려진다.
	void RenderModalOverlay(Graphic& graphic, bool isSettingsOpen) const;
private:
	UIButton* createButton(const Vector& pos, const Vector& size, function<void()> onClick);

	// --------------------------------------------------
	//  HUD 배경 패널 / 골드·HP 텍스트
	// --------------------------------------------------
	void renderHudBackgroundPanel(Graphic& graphic) const;
	void renderGoldText(Graphic& graphic, int32 gold) const;
	void renderHpText(Graphic& graphic, int32 hp) const;
	void renderRoundText(Graphic& graphic, int32 currentRound, int32 totalRound) const;

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

	// --------------------------------------------------
	//  설정 팝업
	// --------------------------------------------------
	void renderSettingsPopup(Graphic& graphic) const;

	// HUD 배경 패널 / 골드·HP 텍스트
	Image* _hudImg = nullptr;
	SpriteAtlas* _hudSprite = nullptr;

	// 웨이브 시작 / 디버그 웨이브 조절
	UIButton* _startButton = nullptr;
	UIButton* _settingsButton = nullptr; // 설정(톱니바퀴) 아이콘. 플레이 버튼 옆, 클릭 시 설정 팝업 토글.
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

	// 설정 팝업: 오륜기 배치(위 3개 + 아래 2개). 아래 왼쪽 버튼이 닫기, 나머지는 아직 자리만 잡음(레이아웃만 구현).
	UIButton* _settingsMenuButtons[5] = {};
	// 각 버튼 가운데 그려질 아이콘(nukki 폴더, 개별 PNG). 순서는 _settingsMenuButtons와 동일: 0 재개, 1 리플레이, 2 자동진행, 3 음악, 4 효과음.
	Image* _settingsIconImgs[5] = {};
	// 2(자동진행)/3(음악)/4(효과음) 버튼의 on/off 토글 상태. true면 꺼짐 — 버튼 위에 nukki/x.png를 겹쳐 그린다.
	// 0(재개)/1(리플레이)는 토글이 아니라서 항상 false로 둔다.
	bool _settingsToggleOff[5] = {};
	Image* _settingsOffMarkImg = nullptr; // nukki/x.png, 꺼짐 표시용

	// 업그레이드 패널 아이콘
	Image* _upgradeIconsImg = nullptr;
	SpriteAtlas* _upgradeIconsSprite = nullptr;
};
