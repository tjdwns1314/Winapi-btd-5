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
	bool canAfford = false;
	string upgradeIconKey;
	wstring upgradeName; // 다음 업그레이드 이름(한글). 업그레이드 패널 아이콘 위쪽에 표시.
	wstring upgradeDescription; // 다음 업그레이드 설명(한글). 업그레이드 버튼에 마우스 올리면 툴팁으로 표시.
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
		function<void()> onGoldAdd,
		function<void()> onHpAdd,
		function<void()> onGoldSub,
		function<void()> onHpSub,
		function<void()> onSellClick,
		function<void()> onUpgradeClick,
		function<void()> onObstacleSellClick,
		function<void()> onRestartClick,
		function<void()> onSettingsClick,
		function<void()> onSettingsCloseClick,
		function<void()> onSettingsReplayClick,
		function<void()> onHomeClick,
		function<void(bool)> onAutoPlayToggle);

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
		bool isGameOver,
		float gameOverFadeProgress);

	// 설정 팝업 전용. 다른 모든 그리기(액터, HUD, 다른 팝업)가 끝난 뒤 프레임 맨 마지막에 호출해야
	// 액터/버튼에 가려지지 않고 항상 최상단에 딤+버튼이 그려진다.
	void RenderModalOverlay(Graphic& graphic, bool isSettingsOpen) const;

	// 상점 호버/업그레이드 툴팁 전용. 배치된 타워 등 액터(Super::Render)보다도 위에 그려야 하므로
	// GameScene::Render에서 액터 렌더링이 끝난 뒤 별도로 호출해야 한다.
	void RenderTooltips(Graphic& graphic, const TowerSelectionInfo& selection) const;

	// 게임오버 딤/문구/재시작 버튼 전용. 게임오버 중에도 계속 움직이는 풍선 등 액터보다 위에 그려야 하므로
	// GameScene::Render에서 액터 렌더링이 끝난 뒤 별도로 호출해야 한다.
	void RenderGameOverPopup(Graphic& graphic, bool isGameOver, float fadeProgress, int32 finalRound) const;
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
	// 작은 사각형 +/- 버튼(배경+기호)을 그린다. 라운드 +/- 및 골드/HP + 버튼이 공용으로 쓴다.
	void renderMiniButton(Graphic& graphic, UIButton* button, bool isPlus) const;

	// --------------------------------------------------
	//  타워/장애물 상점
	// --------------------------------------------------
	void drawTowerIcon(Graphic& graphic, const Vector& pos, TowerType type, float scale) const;
	void renderTowerShopBoxes(Graphic& graphic) const;
	void renderShopIcons(Graphic& graphic) const;
	void renderShopScrollButtons(Graphic& graphic) const;
	void updateShopActiveStates() const;
	// 슬롯 인덱스(0~3) -> 전체 상점 목록 인덱스(0~kShopEntryCount-1) 변환. 0~3=타워, 4=장애물.
	int32 shopEntryIndex(int32 slotIndex) const { return _shopScrollRowOffset * kShopColumns + slotIndex; }

	static constexpr int32 kShopEntryCount = 5;  // 타워 4종 + 장애물 1종
	static constexpr int32 kShopColumns = 2;
	static constexpr int32 kShopVisibleRows = 2; // 2x2 그리드
	static constexpr int32 kShopMaxRowOffset = (kShopEntryCount + kShopColumns - 1) / kShopColumns - kShopVisibleRows;
	void drawObstacleIcon(Graphic& graphic, const Vector& pos, float scale) const;
	void drawRangePreview(Graphic& graphic, const Vector& pos, TowerType type) const;

	// renderTooltipPanel()이 그려준 target_box 안에서 텍스트를 채울 수 있는 좌표.
	struct TooltipLayout
	{
		float textLeft = 0.f;
		float textRight = 0.f;
		float textTop = 0.f;
		float textBottom = 0.f;
	};

	// target_box 배경(사각형 채우기 + 스프라이트)을 그리고 텍스트 좌표를 outLayout에 채운다.
	// X: 오른쪽 HUD 패널 왼쪽에 고정. Y: mouseY를 따라간다. target_box 셀이 없으면 false.
	// renderTowerTooltip / renderUpgradeTooltip이 공용으로 쓰고, 텍스트만 각자 그린다.
	bool renderTooltipPanel(Graphic& graphic, float mouseY, float scaleY, TooltipLayout& outLayout) const;

	// 타워 상점 버튼에 마우스를 올리면 패널만 표시(1단계: 배경만, 텍스트는 다음 단계).
	// target_box를 세로 1.5배로 그리며, X는 오른쪽 HUD 패널 왼쪽에 고정, Y는 마우스를 따라간다.
	void renderTowerTooltip(Graphic& graphic) const;

	// 상점 그리드에서 장애물 칸에 마우스를 올리면 이름/설명을 target_box 패널로 보여준다.
	void renderObstacleShopTooltip(Graphic& graphic) const;

	// 업그레이드 버튼에 마우스를 올리면 다음 업그레이드 설명을 renderTooltipPanel 공용 패널로 보여준다.
	void renderUpgradeTooltip(Graphic& graphic, const TowerSelectionInfo& selection) const;

	// --------------------------------------------------
	//  선택된 타워/장애물 패널 (판매/업그레이드)
	// --------------------------------------------------
	void renderTowerSelectionPanel(Graphic& graphic, const TowerSelectionInfo& selection) const;
	void renderObstacleSelectionPanel(Graphic& graphic, const ObstacleSelectionInfo& selection) const;

	// --------------------------------------------------
	//  게임오버 팝업
	// --------------------------------------------------
	// fadeProgress: 0(딤 시작)→1(완전히 어두워짐). 1이 될 때까지 딤만 그리고, 이후 문구/버튼을 그린다.
	// finalRound: 게임오버가 발생한 시점의 현재 라운드(문구에 "라운드 : N"으로 표시).
	void renderGameOverPopup(Graphic& graphic, float fadeProgress, int32 finalRound) const;

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

	UIButton* _goldAddButton = nullptr; // 골드 +1000 버튼(돈 텍스트 옆)
	UIButton* _hpAddButton = nullptr;   // HP +10 버튼(체력 텍스트 옆)
	UIButton* _goldSubButton = nullptr; // 골드 -1000 버튼(+ 버튼 옆)
	UIButton* _hpSubButton = nullptr;   // HP -10 버튼(+ 버튼 옆)

	// 타워/장애물 상점
	Image* _inGameBg = nullptr;
	SpriteAtlas* _sprite = nullptr;
	UIButton* _shopSlotButtons[4] = {};                     // 2x2 그리드 4칸(내용은 스크롤 오프셋에 따라 바뀜)
	function<void()> _shopEntryCallbacks[kShopEntryCount];  // shopEntryIndex() 순서: Dart/Tack/Sniper/Bomb/Obstacle
	int32 _shopScrollRowOffset = 0;                         // 현재 보이는 시작 "행"(0~kShopMaxRowOffset)
	UIButton* _shopScrollUpButton = nullptr;
	UIButton* _shopScrollDownButton = nullptr;

	// 선택된 타워/장애물 패널 (판매/업그레이드)
	UIButton* _sellButton = nullptr;
	UIButton* _upgradeButton = nullptr;
	UIButton* _obstacleSellButton = nullptr;

	// 게임오버 팝업
	Image* _popupImg = nullptr;
	SpriteAtlas* _popupSprite = nullptr;
	UIButton* _restartButton = nullptr;

	// 설정 팝업: 3x2 격자 배치(위 3개 + 아래 3개). 위 왼쪽 버튼이 닫기, 나머지는 각자 기능 보유.
	UIButton* _settingsMenuButtons[6] = {};
	// 각 버튼 가운데 그려질 아이콘. 0~4는 nukki 폴더 개별 PNG. 5(홈)는 nullptr — game_over_popup.xml의
	// home_icon_shared 셀을 _popupImg/_popupSprite로 그린다(renderSettingsPopup 참고).
	// 순서: 0 재개, 1 리플레이, 2 자동진행, 3 음악, 4 효과음, 5 로비로 이동.
	Image* _settingsIconImgs[6] = {};
	// 2(자동진행)/3(음악)/4(효과음) 버튼의 on/off 토글 상태. true면 꺼짐 — 버튼 위에 nukki/x.png를 겹쳐 그린다.
	// 0(재개)/1(리플레이)/5(홈)는 토글이 아니라서 항상 false로 둔다.
	bool _settingsToggleOff[6] = {};
	Image* _settingsOffMarkImg = nullptr; // nukki/x.png, 꺼짐 표시용

	// 업그레이드 패널 아이콘
	Image* _upgradeIconsImg = nullptr;
	SpriteAtlas* _upgradeIconsSprite = nullptr;
};
