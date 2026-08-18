#include "pch.h"
#include "GameSceneUI.h"
#include "UIManager.h"
#include "ResourceManager.h"

namespace
{
	// --------------------------------------------------
	//  HUD 배경 패널 / 골드·HP 텍스트
	// --------------------------------------------------
	// 오른쪽 상단 골드/HP 아이콘+숫자 배치. 임시값 — 빌드 후 눈으로 보고 조정 필요(미검증).
	constexpr float kHudIconCenterX = 1520.0f;
	constexpr float kHudTextLeft = 1575.0f;
	constexpr float kHudTextRight = 1745.0f;
	constexpr float kGoldIconCenterY = 100.0f;
	constexpr float kHpIconCenterY = 200.0f;
	const D2D1::ColorF kHudTextColor = D2D1::ColorF(D2D1::ColorF::White);

	// 상단 HUD 패널(side_hud_bg_01, side_hud_scroll) 가로 폭(px). 이 값만 바꾸면 두 패널 폭이 함께 조절됨.
	// 원본 폭 274px, UI 영역 왼쪽 끝에서부터 이 폭만큼만 그려짐(끝까지 채우려면 kUiPanelWidth와 동일한 320으로).
	constexpr float kHudPanelWidth = 300.0f;

	// --------------------------------------------------
	//  웨이브 시작 / 디버그 웨이브 조절
	// --------------------------------------------------
	// 웨이브 시작 버튼 위치 및 원본 스프라이트 크기(128x129)에 곱할 배율.
	const Vector kStartButtonPos = Vector(1485.0f, 1000.0f);
	constexpr float kStartButtonBaseWidth = 128.0f;
	constexpr float kStartButtonBaseHeight = 129.0f;
	// 플레이(웨이브 시작) 버튼과 그 옆 설정 아이콘 크기 배율.
	constexpr float kPlayButtonScale = 0.6f;
	// 설정 아이콘(pause_icon) 표시 위치 — 플레이 버튼(1512.5, 950) 옆에 나란히. 임시값(미검증).
	constexpr float kSettingsIconCenterX = 1575.0f;
	constexpr float kSettingsIconCenterY = 1000.0f;

	// 디버그 웨이브 +/- 버튼 위치·크기 (정식 스프라이트 없이 도형으로 그림)
	const Vector kWaveUpButtonPos = Vector(1720.0f, 1000.0f);
	const Vector kWaveDownButtonPos = Vector(1720.0f, 1050.0f);
	const Vector kWaveButtonSize = Vector(40.0f, 40.0f);

	// --------------------------------------------------
	//  타워/장애물 상점
	// --------------------------------------------------
	// 타워 상점 버튼: 스크롤 패널(y=270~518) 안 2x2 그리드 위치. 클릭 판정 크기는
	// tower_thumbs_box 배경(renderTowerShopBoxes)과 맞춘다.
	const Vector kDartShopButtonPos = Vector(1520.0f, 332.0f);
	const Vector kTackShopButtonPos = Vector(1680.0f, 332.0f);
	const Vector kSniperShopButtonPos = Vector(1520.0f, 456.0f);
	const Vector kBombShopButtonPos = Vector(1680.0f, 456.0f);
	const Vector kTowerShopButtonSize = Vector(113.0f, 93.0f);
	constexpr float kTowerIconScale = 0.7f;

	// 장애물 상점 버튼 위치·크기 및 아이콘 배율. 위치는 임시값 — 빌드 후 눈으로 보고 조정할 것.
	const Vector kObstacleShopButtonPos = Vector(1675.0f, 1000.0f);
	const Vector kObstacleShopButtonSize = Vector(109.0f, 113.0f);
	constexpr float kObstacleIconScale = 1.0f;

	// --------------------------------------------------
	//  선택된 타워/장애물 패널 (판매/업그레이드)
	// --------------------------------------------------
	// 판매 버튼 배경(sell_box) 가로 스케일. 원본이 288x76로 가로가 길어 오른쪽 UI 패널 폭에
	// 맞추려면 가로만 축소해야 한다. 이 값만 바꾸면 판매 버튼 크기(시각+클릭 판정)가 함께 조절됨.
	constexpr float kSellBoxScaleX = 0.7f;

	// 타워 선택 패널: 상점 버튼(y=550)과 웨이브 버튼(y=900) 사이 빈 공간에 고정 배치.
	// 위치/크기는 임시값 — 빌드 후 눈으로 보고 조정할 것.
	const Vector kSellButtonPos = Vector(1600.0f, 920.0f);
	const Vector kSellButtonFallbackSize = Vector(109.0f, 60.0f); // sell_box 셀을 못 찾았을 때 대비
	const Vector kUpgradeButtonPos = Vector(1600.0f, 800.0f);
	const Vector kUpgradeButtonFallbackSize = Vector(109.0f, 60.0f); // upgrade_box 셀을 못 찾았을 때 대비
	const Vector kObstacleSellButtonPos = Vector(1837.5f, 800.0f);

	// upgrade_box_buy/cant 배경(284x226, 정사각형에 가까움) 축소 배율.
	// 이 값만 바꾸면 업그레이드 버튼 크기(시각+클릭 판정)가 함께 조절됨. 임시값 — 빌드 후 눈으로 보고 조정할 것.
	constexpr float kUpgradeBoxScale = 0.6f;

	// 타워 이름 아래 등급별 초상화 박스(tower_profile_pic_box, 196x222) 위치·배율.
	// 이름 텍스트(y=520~600)와 업그레이드 박스(y=800) 사이 빈 공간에 배치. 임시값 — 빌드 후 눈으로 보고 조정할 것.
	const Vector kAvatarBoxPos = Vector(1600.0f, 640.0f);
	constexpr float kAvatarBoxScale = 0.7f;
	// 초상화(avatarKey) 자체의 배율. 박스보다 작게 그려서 프레임 안에 들어오도록. 임시값 — 빌드 후 눈으로 보고 조정할 것.
	constexpr float kAvatarImageScale = 0.5f;

	// 업그레이드 아이콘은 박스 위쪽에, 가격 텍스트는 아래쪽 좁은 띠에. 임시값 — 빌드 후 눈으로 보고 조정할 것.
	constexpr float kUpgradeIconOffsetY = -12.0f;
	constexpr float kUpgradeIconScale = 0.9f;
	constexpr float kUpgradePriceTextHeight = 24.0f;

	// 선택 패널 문구 및 이름/레벨 텍스트 표시 영역·색상
	const wchar_t* const kSellTextFormat = L"판매: %d";
	const wchar_t* const kUpgradeTextFormat = L"%d"; // 가격 숫자만 표시
	const wchar_t* const kUpgradeMaxedText = L"업그레이드 경로 달함"; // 최고 등급 도달 시 표시
	const wchar_t* const kNameLevelTextFormat = L"%s 레벨 %d";
	constexpr D2D1_RECT_F kNameLevelTextRect = { 1450.0f, 520.0f, 1740.0f, 600.0f };
	const D2D1::ColorF kNameLevelTextColor = D2D1::ColorF(D2D1::ColorF::Yellow);

	// --------------------------------------------------
	//  게임오버 팝업
	// --------------------------------------------------
	// 재시작 버튼: baked 이미지(131x137) 크기에 맞춰 게임 영역 정중앙에 둔다.
	const Vector kRestartButtonSize = Vector(131.0f, 137.0f);
	const wchar_t* const kGameOverText = L"GAME OVER";
	const D2D1::ColorF kGameOverTextColor = D2D1::ColorF(D2D1::ColorF::Red);
	const D2D1::ColorF kGameOverDimColor = D2D1::ColorF(D2D1::ColorF::Black, 0.6f);
	constexpr float kGameOverTextTopOffset = -160.0f;
	constexpr float kGameOverTextBottomOffset = -80.0f;

	// --------------------------------------------------
	//  설정 팝업 (오륜기 배치)
	// --------------------------------------------------
	// plain_button(131x137) 5개를 오륜기처럼 배치: 위 3개, 아래 2개(위 버튼 사이 아래에 걸치도록).
	// 배열 순서: 0,1,2 = 위쪽 왼→오, 3,4 = 아래쪽 왼→오. 0번(위 왼쪽)이 재개(닫기) 버튼.
	// 위치는 게임 영역 정중앙 기준 임시값 — 빌드 후 눈으로 보고 조정할 것(미검증).
	// 각 버튼 아이콘 파일(Resource/Sprite/nukki). 순서: 0 재개, 1 리플레이, 2 자동진행, 3 음악, 4 효과음.
	const wchar_t* const kSettingsIconFiles[5] = {
		L"Resource\\Sprite\\nukki\\resume.png",
		L"Resource\\Sprite\\nukki\\replay.png",
		L"Resource\\Sprite\\nukki\\autoplay.png",
		L"Resource\\Sprite\\nukki\\music.png",
		L"Resource\\Sprite\\nukki\\sfx.png",
	};
	constexpr float kSettingsIconScale = 1.0f; // 아이콘 원본 크기 배율. 버튼(plain_button, kSettingsRingScale 적용) 안에 들어오도록 임시값 — 눈으로 보고 조정할 것(미검증).
	constexpr float kSettingsOffMarkScale = 0.25f; // nukki/x.png 원본이 커서 축소. EditorScene 확인 코드에서 쓰던 값 그대로 가져옴(미검증).
	constexpr float kSettingsButtonBaseWidth = 128.0f;  // plain_button 원본 스프라이트 가로 크기(px). 클릭 판정 크기 계산에 사용.
	constexpr float kSettingsButtonBaseHeight = 129.0f; // plain_button 원본 스프라이트 세로 크기(px). 클릭 판정 크기 계산에 사용.
	constexpr float kSettingsRingSpacingX = 250.0f;     // 위쪽 3개 버튼 사이 가로 간격, 아래쪽 2개 버튼 가로 오프셋(간격의 절반)에도 쓰임.
	constexpr float kSettingsRingSpacingY = 200.0f;     // 위쪽 줄과 아래쪽 줄 사이 세로 간격.
	constexpr float kSettingsRingScale = 1.5f;          // 버튼 원본 크기(128x129)에 곱하는 배율 — 실제 그려지는 크기 + 클릭 판정 크기가 함께 커진다.
	constexpr float kSettingsRingCenterOffsetY = -150.0f;  // 5개 버튼 그룹 전체를 위(-)/아래(+)로 한 번에 밀 때 쓰는 값. 게임 영역 정중앙(GameAreaCenterY) 기준.
	const D2D1::ColorF kSettingsDimColor = D2D1::ColorF(D2D1::ColorF::Black, 0.6f);
}

void GameSceneUI::Init(
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
	function<void()> onSettingsCloseClick)
{
	ResourceManager& res = ResourceManager::GetInstance();
	// HUD 배경 패널
	_hudImg = &res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");
	// 타워/장애물 상점 아이콘
	_inGameBg = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_sprite = &res.GetAtlas(L"Resource\\Sprite\\InGame.xml");
	// 게임오버 팝업
	_popupImg = &res.GetImage(L"Resource\\Sprite\\game_over_popup.png");
	_popupSprite = &res.GetAtlas(L"Resource\\Sprite\\game_over_popup.xml");
	// 업그레이드 패널 아이콘
	_upgradeIconsImg = &res.GetImage(L"Resource\\Sprite\\upgrade_icons.png");
	_upgradeIconsSprite = &res.GetAtlas(L"Resource\\Sprite\\upgrade_icons.xml");

	// 웨이브 시작 버튼
	_startButton = createButton(kStartButtonPos, Vector(kStartButtonBaseWidth * kPlayButtonScale, kStartButtonBaseHeight * kPlayButtonScale), onStartWave);

	// 설정(톱니바퀴) 버튼. 플레이 버튼 옆에 나란히, 클릭 시 설정 팝업 토글.
	_settingsButton = createButton(Vector(kSettingsIconCenterX, kSettingsIconCenterY),
		Vector(kStartButtonBaseWidth * kPlayButtonScale, kStartButtonBaseHeight * kPlayButtonScale), onSettingsClick);
	_settingsButton->SetIgnoresModalLock(true); // 설정창이 열려 있어도(입력 잠금) 이 버튼 자체는 계속 눌려야 닫을 수 있다.

	// 타워 상점 버튼: 스크롤 패널(y=270~518) 안에 2x2 그리드로 배치.
	// 클릭 판정 크기는 실제로 그려지는 tower_thumbs_box 배경(113x93, renderTowerShopBoxes 참고)과 맞춘다.
	_dartMonkeyShopButton = createButton(kDartShopButtonPos, kTowerShopButtonSize, onDartShopClick);
	_tackShooterShopButton = createButton(kTackShopButtonPos, kTowerShopButtonSize, onTackShopClick);
	_sniperMonkeyShopButton = createButton(kSniperShopButtonPos, kTowerShopButtonSize, onSniperShopClick);
	_bombTowerShopButton = createButton(kBombShopButtonPos, kTowerShopButtonSize, onBombShopClick);
	_obstacleShopButton = createButton(kObstacleShopButtonPos, kObstacleShopButtonSize, onObstacleShopClick);

	// 디버그 웨이브 +/- 버튼
	_waveUpButton = createButton(kWaveUpButtonPos, kWaveButtonSize, onWaveUp);
	_waveDownButton = createButton(kWaveDownButtonPos, kWaveButtonSize, onWaveDown);

	// 타워 선택 패널: 상점 버튼(y=550)과 웨이브 버튼(y=900) 사이 빈 공간에 고정 배치.
	// 위치/크기는 임시값 — 빌드 후 눈으로 보고 조정할 것.
	// 클릭 판정 크기는 sell_box 스프라이트가 실제로 그려지는 크기(가로 kSellBoxScaleX 배율 적용)와
	// 항상 같게 맞춘다 — kSellBoxScaleX를 바꾸면 시각 크기와 판정 크기가 함께 바뀐다.
	Vector sellButtonSize = kSellButtonFallbackSize;
	if (const CellInfo* sellBoxCell = _hudSprite->GetCell("sell_box"))
		sellButtonSize = Vector(sellBoxCell->aw * kSellBoxScaleX, sellBoxCell->ah);

	// 업그레이드 버튼도 sell_box와 동일하게, 실제로 그려지는 upgrade_box 스프라이트 크기(축소 배율 적용)와
	// 클릭 판정 크기를 맞춘다.
	Vector upgradeButtonSize = kUpgradeButtonFallbackSize;
	if (const CellInfo* upgradeBoxCell = _hudSprite->GetCell("upgrade_box_buy"))
		upgradeButtonSize = Vector(upgradeBoxCell->aw * kUpgradeBoxScale, upgradeBoxCell->ah * kUpgradeBoxScale);

	_sellButton = createButton(kSellButtonPos, sellButtonSize, onSellClick);
	_upgradeButton = createButton(kUpgradeButtonPos, upgradeButtonSize, onUpgradeClick);
	_sellButton->SetActive(false);
	_upgradeButton->SetActive(false);

	_obstacleSellButton = createButton(kObstacleSellButtonPos, sellButtonSize, onObstacleSellClick);
	_obstacleSellButton->SetActive(false);

	// 게임오버 팝업의 재시작 버튼. baked 이미지(131x137) 크기에 맞춰 게임 영역 정중앙에 둔다.
	_restartButton = createButton(Vector(GameAreaCenterX, GameAreaCenterY), kRestartButtonSize, onRestartClick);
	_restartButton->SetActive(false);

	// 설정 팝업 버튼 5개: 오륜기 배치. 게임 영역 정중앙 기준.
	const Vector settingsButtonSize(kSettingsButtonBaseWidth * kSettingsRingScale, kSettingsButtonBaseHeight * kSettingsRingScale);
	const Vector ringOffsets[5] = {
		Vector(-kSettingsRingSpacingX, 0.0f),                          // 0: 위 왼쪽
		Vector(0.0f, 0.0f),                                            // 1: 위 가운데
		Vector(kSettingsRingSpacingX, 0.0f),                           // 2: 위 오른쪽
		Vector(-kSettingsRingSpacingX * 0.5f, kSettingsRingSpacingY),  // 3: 아래 왼쪽
		Vector(kSettingsRingSpacingX * 0.5f, kSettingsRingSpacingY),   // 4: 아래 오른쪽
	};
	_settingsOffMarkImg = &res.GetImage(L"Resource\\Sprite\\nukki\\x.png");

	for (int32 i = 0; i < 5; ++i)
	{
		const Vector pos = Vector(GameAreaCenterX + ringOffsets[i].x, GameAreaCenterY + kSettingsRingCenterOffsetY + ringOffsets[i].y);
		function<void()> onClick;
		if (i == 0)
			onClick = onSettingsCloseClick; // 0번(위 왼쪽) = 재개
		else if (i == 2 || i == 3 || i == 4) // 2,3,4번 = 자동진행/음악/효과음 — 클릭할 때마다 on/off 토글
			onClick = [this, i]() { _settingsToggleOff[i] = !_settingsToggleOff[i]; };
		else
			onClick = []() {};
		_settingsMenuButtons[i] = createButton(pos, settingsButtonSize, onClick);
		_settingsMenuButtons[i]->SetActive(false);
		_settingsMenuButtons[i]->SetIgnoresModalLock(true); // 설정창 자신의 버튼들이라 입력 잠금 대상에서 제외.
		_settingsIconImgs[i] = &res.GetImage(kSettingsIconFiles[i]);
	}
	// 자동진행(2번, 위 오른쪽)만 기본값이 꺼짐 상태 — 나머지 토글(음악/효과음)은 기본 켜짐.
	_settingsToggleOff[2] = true;
}

UIButton* GameSceneUI::createButton(const Vector& pos, const Vector& size, function<void()> onClick)
{
	UIButton* button = new UIButton();
	button->SetPos(pos);
	button->SetSize(size);
	button->SetActive(true);
	button->SetOnClick(onClick);
	UIManager::GetInstance().Register(button);
	return button;
}

void GameSceneUI::Render(Graphic& graphic, bool isDraggingTower, TowerType draggingTowerType,
	bool isDraggingObstacle,
	const Vector& dragPreviewPos, const TowerSelectionInfo& selection,
	const ObstacleSelectionInfo& obstacleSelection,
	int32 hp, int32 gold, bool isWaveActive, bool isSpeedEnabled,
	bool isGameOver)
{
	renderHudBackgroundPanel(graphic);

	renderStartButton(graphic, isWaveActive, isSpeedEnabled);

	renderTowerShopBoxes(graphic);

	if (_dartMonkeyShopButton != nullptr) drawTowerIcon(graphic, _dartMonkeyShopButton->GetPos(), TowerType::DartMonkey, kTowerIconScale);
	if (_tackShooterShopButton != nullptr) drawTowerIcon(graphic, _tackShooterShopButton->GetPos(), TowerType::TackShooter, kTowerIconScale);
	if (_sniperMonkeyShopButton != nullptr) drawTowerIcon(graphic, _sniperMonkeyShopButton->GetPos(), TowerType::SniperMonkey, kTowerIconScale);
	if (_bombTowerShopButton != nullptr) drawTowerIcon(graphic, _bombTowerShopButton->GetPos(), TowerType::BombTower, kTowerIconScale);
	if (_obstacleShopButton != nullptr) drawObstacleIcon(graphic, _obstacleShopButton->GetPos(), kObstacleIconScale);

	if (isDraggingTower)
	{
		drawRangePreview(graphic, dragPreviewPos, draggingTowerType);
		drawTowerIcon(graphic, dragPreviewPos, draggingTowerType, kTowerIconScale);
	}
	if (isDraggingObstacle)
		drawObstacleIcon(graphic, dragPreviewPos, kObstacleIconScale);

	renderDebugWaveButtons(graphic);
	renderGoldText(graphic, gold);
	renderHpText(graphic, hp);

	if (_sellButton != nullptr) _sellButton->SetActive(selection.isSelected);
	if (_upgradeButton != nullptr) _upgradeButton->SetActive(selection.isSelected && selection.canUpgrade);
	if (selection.isSelected)
		renderTowerSelectionPanel(graphic, selection);

	if (_obstacleSellButton != nullptr) _obstacleSellButton->SetActive(obstacleSelection.isSelected);
	if (obstacleSelection.isSelected)
		renderObstacleSelectionPanel(graphic, obstacleSelection);

	if (_restartButton != nullptr) _restartButton->SetActive(isGameOver);
	if (isGameOver)
		renderGameOverPopup(graphic);
}

void GameSceneUI::RenderModalOverlay(Graphic& graphic, bool isSettingsOpen) const
{
	for (UIButton* button : _settingsMenuButtons)
		if (button != nullptr) button->SetActive(isSettingsOpen);

	if (isSettingsOpen)
		renderSettingsPopup(graphic);
}

// --------------------------------------------------
//  HUD 배경 패널 / 골드·HP 텍스트
// --------------------------------------------------

// 오른쪽 UI 영역 배경. 맨 아래에 하단 배경을 깔고, 그 위에 상단 패널들을 겹쳐 그린다.
void GameSceneUI::renderHudBackgroundPanel(Graphic& graphic) const
{
	constexpr float kUiPanelWidth = static_cast<float>(GWinSizeX - GameAreaWidth);
	const float centerX = static_cast<float>(GameAreaWidth) + kUiPanelWidth * 0.5f;

	// 1. 맨 아래 깔리는 하단 배경(lower_hud_bg_01, 90도 회전). 가로폭에 맞춰 비율 유지로
	//    스케일(찌그러짐 없음)한 뒤 화면 맨 아래에 붙인다. 이미지 자체 높이가 남는 공간보다
	//    커서 1장으로 바닥까지 닿고, 위쪽 남는 부분은 2/3번 패널에 가려진다.
	if (const CellInfo* cell = _hudSprite->GetCell("lower_hud_bg_01"))
	{
		const float scale = kUiPanelWidth / cell->ah; // 회전 전 세로(ah=256, 회전 후 가로가 됨)를 UI 패널 가로폭에 맞춤
		const float tileHeight = cell->aw * scale;    // 회전 전 가로(aw=1774, 회전 후 세로가 됨)
		const float centerY = static_cast<float>(GWinSizeY) - tileHeight * 0.5f;
		_hudImg->DrawSprite(graphic, centerX, centerY, *cell, scale, 90.0f);
	}

	// 2. 상단 배경(side_hud_bg_01, 높이 270) — kHudPanelWidth만큼 UI 영역 왼쪽 끝에 붙인다.
	if (const CellInfo* cell = _hudSprite->GetCell("side_hud_bg_01"))
	{
		constexpr float kPanelCenterY = 135.0f;
		const float panelCenterX = static_cast<float>(GameAreaWidth) + kHudPanelWidth * 0.5f;
		const float scaleX = kHudPanelWidth / cell->aw;
		_hudImg->DrawSprite(graphic, panelCenterX, kPanelCenterY, *cell, scaleX, 0.0f, false, 1.0f);
	}

	// 3. 그 아래 이어지는 스크롤 배경(side_hud_scroll, 높이 248) — kHudPanelWidth만큼 UI 영역 왼쪽 끝에 붙인다.
	if (const CellInfo* cell = _hudSprite->GetCell("side_hud_scroll"))
	{
		constexpr float kScrollCenterY = 270.0f + 248.0f * 0.5f; // 상단 배경 높이(270) + 이 패널 높이(248)/2
		const float panelCenterX = static_cast<float>(GameAreaWidth) + kHudPanelWidth * 0.5f;
		const float scaleX = kHudPanelWidth / cell->aw;
		_hudImg->DrawSprite(graphic, panelCenterX, kScrollCenterY, *cell, scaleX, 0.0f, false, 1.0f);
	}
}

void GameSceneUI::renderGoldText(Graphic& graphic, int32 gold) const
{
	if (const CellInfo* cell = _hudSprite->GetCell("cash_icon"))
		_hudImg->DrawSprite(graphic, kHudIconCenterX, kGoldIconCenterY, *cell);

	wchar_t text[32];
	swprintf_s(text, L"%d", gold);

	graphic.DrawString(text, D2D1::RectF(kHudTextLeft, kGoldIconCenterY - 25.0f, kHudTextRight, kGoldIconCenterY + 25.0f),
		FONT_30, kHudTextColor, DWRITE_TEXT_ALIGNMENT_LEADING);
}

void GameSceneUI::renderHpText(Graphic& graphic, int32 hp) const
{
	if (const CellInfo* cell = _hudSprite->GetCell("lives_icon"))
		_hudImg->DrawSprite(graphic, kHudIconCenterX, kHpIconCenterY, *cell);

	wchar_t text[32];
	swprintf_s(text, L"%d", hp);

	graphic.DrawString(text, D2D1::RectF(kHudTextLeft, kHpIconCenterY - 25.0f, kHudTextRight, kHpIconCenterY + 25.0f),
		FONT_30, kHudTextColor, DWRITE_TEXT_ALIGNMENT_LEADING);
}

// --------------------------------------------------
//  웨이브 시작 / 디버그 웨이브 조절
// --------------------------------------------------

void GameSceneUI::renderStartButton(Graphic& graphic, bool isWaveActive, bool isSpeedEnabled) const
{
	const char* cellName = "play_icon";
	if (isWaveActive)
		cellName = isSpeedEnabled ? "ff_icon_red" : "ff_icon";

	if (const CellInfo* cell = _hudSprite->GetCell(cellName))
	{
		const Vector pos = _startButton->GetPos();
		_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, kPlayButtonScale, 0.0f);
	}

	// 설정 아이콘(pause_icon). 플레이 버튼 옆에 나란히 같은 배율로 표시하며, 클릭하면 설정 팝업이 열린다.
	if (const CellInfo* cell = _hudSprite->GetCell("pause_icon"))
	{
		const Vector pos = _settingsButton->GetPos();
		_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, kPlayButtonScale, 0.0f);
	}
}

void GameSceneUI::renderDebugWaveButtons(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	if (renderTarget == nullptr)
		return;

	auto drawButton = [&](UIButton* button, bool isPlus)
	{
		if (button == nullptr)
			return;

		const Vector pos = button->GetPos();
		const Vector size = button->GetSize();
		const D2D1_RECT_F rect = D2D1::RectF(
			pos.x - size.x * 0.5f,
			pos.y - size.y * 0.5f,
			pos.x + size.x * 0.5f,
			pos.y + size.y * 0.5f);

		ID2D1SolidColorBrush* bgBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::DarkGray, 0.8f));
		if (bgBrush != nullptr)
			renderTarget->FillRectangle(rect, bgBrush);

		const float cx = pos.x;
		const float cy = pos.y;
		const float half = size.x * 0.3f;
		const float thickness = 4.0f;

		ID2D1SolidColorBrush* markBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::White));
		if (markBrush == nullptr)
			return;

		renderTarget->FillRectangle(
			D2D1::RectF(cx - half, cy - thickness * 0.5f, cx + half, cy + thickness * 0.5f), markBrush);

		if (isPlus)
		{
			renderTarget->FillRectangle(
				D2D1::RectF(cx - thickness * 0.5f, cy - half, cx + thickness * 0.5f, cy + half), markBrush);
		}
	};

	drawButton(_waveUpButton, true);
	drawButton(_waveDownButton, false);
}

// --------------------------------------------------
//  타워/장애물 상점
// --------------------------------------------------

void GameSceneUI::drawTowerIcon(Graphic& graphic, const Vector& pos, TowerType type, float scale) const
{
	const TowerVisual& visual = GetTowerVisual(type);

	if (visual.useBakedImage)
	{
		ResourceManager::GetInstance().GetImage(visual.bakedImageKey.c_str()).Draw(graphic, pos.x, pos.y, scale, 0.0f);
		return;
	}

	if (_sprite != nullptr && _inGameBg != nullptr)
	{
		if (const CellInfo* cell = _sprite->GetCell(visual.cellName.c_str()))
			_inGameBg->DrawSprite(graphic, pos.x, pos.y, *cell, scale, 0.0f);
	}
}

// 타워 상점 버튼 4개 자리에 tower_thumbs_box 배경을 2x2로 깔아준다(아이콘보다 먼저 그려야 함).
void GameSceneUI::renderTowerShopBoxes(Graphic& graphic) const
{
	const CellInfo* cell = _hudSprite->GetCell("tower_thumbs_box");
	if (cell == nullptr)
		return;

	auto drawBox = [&](UIButton* button)
	{
		if (button == nullptr)
			return;
		const Vector pos = button->GetPos();
		_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, 1.0f, 0.0f);
	};

	drawBox(_dartMonkeyShopButton);
	drawBox(_tackShooterShopButton);
	drawBox(_sniperMonkeyShopButton);
	drawBox(_bombTowerShopButton);
}

void GameSceneUI::drawObstacleIcon(Graphic& graphic, const Vector& pos, float scale) const
{
	if (_sprite == nullptr || _inGameBg == nullptr)
		return;

	const ObstacleStat& stat = GetObstacleStat(ObstacleType::BananaFarmTree);
	if (const CellInfo* cell = _sprite->GetCell(stat.cellName.c_str()))
		_inGameBg->DrawSprite(graphic, pos.x, pos.y, *cell, scale, 0.0f);
}

void GameSceneUI::drawRangePreview(Graphic& graphic, const Vector& pos, TowerType type) const
{
	if (type == TowerType::SniperMonkey)
		return;

	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Black, 0.35f));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	const float range = GetTowerStat(type).grades.front().attackRange;
	renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), range, range), brush);
}

// --------------------------------------------------
//  선택된 타워/장애물 패널 (판매/업그레이드)
// --------------------------------------------------

void GameSceneUI::renderTowerSelectionPanel(Graphic& graphic, const TowerSelectionInfo& selection) const
{
	// 판매 버튼 배경은 sell_box 스프라이트를 가로만 축소해서 그린다.
	auto drawSellBoxBg = [&](UIButton* button)
	{
		if (const CellInfo* cell = _hudSprite->GetCell("sell_box"))
		{
			const Vector pos = button->GetPos();
			_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, kSellBoxScaleX, 0.0f, false, 1.0f);
		}
	};

	// 업그레이드 버튼 배경: 돈이 되면 upgrade_box_buy, 안 되면 upgrade_box_cant.
	auto drawUpgradeBoxBg = [&](UIButton* button, bool canUpgrade)
	{
		const char* cellName = canUpgrade ? "upgrade_box_buy" : "upgrade_box_cant";
		if (const CellInfo* cell = _hudSprite->GetCell(cellName))
		{
			const Vector pos = button->GetPos();
			_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, kUpgradeBoxScale, 0.0f);
		}
	};

	auto drawPriceText = [&](UIButton* button, const wchar_t* text)
	{
		const Vector pos = button->GetPos();
		const Vector size = button->GetSize();
		graphic.DrawString(text, D2D1::RectF(
			pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
			pos.x + size.x * 0.5f, pos.y + size.y * 0.5f),
			FONT_20, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER,
			DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	};

	drawSellBoxBg(_sellButton);
	wchar_t sellText[32];
	swprintf_s(sellText, kSellTextFormat, selection.sellPrice);
	drawPriceText(_sellButton, sellText);

	drawUpgradeBoxBg(_upgradeButton, selection.canUpgrade);

	if (selection.canUpgrade)
	{
		// 다음 업그레이드 아이콘(위쪽)과 가격(아래쪽 좁은 띠)을 함께 보여준다.
		if (!selection.upgradeIconKey.empty())
		{
			if (const CellInfo* iconCell = _upgradeIconsSprite->GetCell(selection.upgradeIconKey.c_str()))
			{
				const Vector pos = _upgradeButton->GetPos();
				_upgradeIconsImg->DrawSprite(graphic, pos.x, pos.y + kUpgradeIconOffsetY, *iconCell, kUpgradeIconScale, 0.0f);
			}
		}

		wchar_t upgradeText[32];
		swprintf_s(upgradeText, kUpgradeTextFormat, selection.upgradePrice);
		const Vector pos = _upgradeButton->GetPos();
		const Vector size = _upgradeButton->GetSize();
		graphic.DrawString(upgradeText, D2D1::RectF(
			pos.x - size.x * 0.5f, pos.y + size.y * 0.5f - kUpgradePriceTextHeight,
			pos.x + size.x * 0.5f, pos.y + size.y * 0.5f),
			FONT_20, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER,
			DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	else
	{
		// 최고 등급 도달 — 아이콘/가격 대신 박스 전체에 안내 문구를 표시.
		const Vector pos = _upgradeButton->GetPos();
		const Vector size = _upgradeButton->GetSize();
		graphic.DrawString(kUpgradeMaxedText, D2D1::RectF(
			pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
			pos.x + size.x * 0.5f, pos.y + size.y * 0.5f),
			FONT_12, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER,
			DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	if (const CellInfo* avatarBoxCell = _hudSprite->GetCell("tower_profile_pic_box"))
		_hudImg->DrawSprite(graphic, kAvatarBoxPos.x, kAvatarBoxPos.y, *avatarBoxCell, kAvatarBoxScale, 0.0f);

	if (!selection.avatarKey.empty())
	{
		if (const CellInfo* avatarCell = _hudSprite->GetCell(selection.avatarKey.c_str()))
			_hudImg->DrawSprite(graphic, kAvatarBoxPos.x, kAvatarBoxPos.y, *avatarCell, kAvatarImageScale, 0.0f);
	}

	wchar_t nameLevelText[64];
	swprintf_s(nameLevelText, kNameLevelTextFormat, selection.name, selection.grade);
	graphic.DrawString(nameLevelText, kNameLevelTextRect,
		FONT_20, kNameLevelTextColor, DWRITE_TEXT_ALIGNMENT_CENTER);
}

void GameSceneUI::renderObstacleSelectionPanel(Graphic& graphic, const ObstacleSelectionInfo& selection) const
{
	const Vector pos = _obstacleSellButton->GetPos();
	const Vector size = _obstacleSellButton->GetSize();

	if (const CellInfo* cell = _hudSprite->GetCell("sell_box"))
		_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, kSellBoxScaleX, 0.0f, false, 1.0f);

	wchar_t sellText[32];
	swprintf_s(sellText, kSellTextFormat, selection.sellPrice);
	graphic.DrawString(sellText, D2D1::RectF(
		pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
		pos.x + size.x * 0.5f, pos.y + size.y * 0.5f),
		FONT_20, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER,
		DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

// --------------------------------------------------
//  게임오버 팝업
// --------------------------------------------------

void GameSceneUI::renderGameOverPopup(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* dimBrush = graphic.GetBrush(kGameOverDimColor);
	if (renderTarget != nullptr && dimBrush != nullptr)
	{
		// game_over_popup.xml에는 배경 패널 셀이 없어서, 게임 영역 전체를 어둡게 깔아 팝업처럼 보이게 한다.
		renderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f,
			static_cast<float>(GameAreaWidth), static_cast<float>(GameAreaHeight)), dimBrush);
	}

	graphic.DrawString(kGameOverText,
		D2D1::RectF(0.0f, GameAreaCenterY + kGameOverTextTopOffset, static_cast<float>(GameAreaWidth), GameAreaCenterY + kGameOverTextBottomOffset),
		FONT_30, kGameOverTextColor, DWRITE_TEXT_ALIGNMENT_CENTER);

	ResourceManager::GetInstance().GetImage(L"restart_button_baked")
		.Draw(graphic, GameAreaCenterX, GameAreaCenterY, 1.0f, 0.0f);
}

// --------------------------------------------------
//  설정 팝업
// --------------------------------------------------

void GameSceneUI::renderSettingsPopup(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* dimBrush = graphic.GetBrush(kSettingsDimColor);
	if (renderTarget != nullptr && dimBrush != nullptr)
	{
		// 게임 필드뿐 아니라 오른쪽 상점 HUD까지 포함해 화면 전체를 어둡게 덮는다.
		renderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f,
			static_cast<float>(GWinSizeX), static_cast<float>(GWinSizeY)), dimBrush);
	}

	const CellInfo* cell = _hudSprite->GetCell("plain_button");
	if (cell == nullptr)
		return;

	for (int32 i = 0; i < 5; ++i)
	{
		UIButton* button = _settingsMenuButtons[i];
		if (button == nullptr)
			continue;
		const Vector pos = button->GetPos();
		_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, kSettingsRingScale, 0.0f);

		if (_settingsIconImgs[i] != nullptr)
			_settingsIconImgs[i]->Draw(graphic, pos.x, pos.y, kSettingsIconScale, 0.0f);

		if (_settingsToggleOff[i] && _settingsOffMarkImg != nullptr)
			_settingsOffMarkImg->Draw(graphic, pos.x, pos.y, kSettingsOffMarkScale, 0.0f);
	}
}
