#include "pch.h"
#include "GameSceneUI.h"
#include "UIManager.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "InputManager.h"

namespace
{
	// --------------------------------------------------
	//  HUD 배경 패널 (오른쪽 UI 영역 배경 이미지)
	// --------------------------------------------------
	// 상단 배경(side_hud_bg_01) + 스크롤 배경(side_hud_scroll) 가로 폭(px), 공통으로 씀.
	// 원본 폭 274px, UI 영역 왼쪽 끝에서부터 이 폭만큼만 그려짐(끝까지 채우려면 kUiPanelWidth와 동일한 320으로).
	// 이 값 하나만 바꾸면 두 패널 폭이 함께 조절됨.
	constexpr float kHudPanelWidth = 300.0f;

	// --------------------------------------------------
	//  골드 / HP 아이콘 + 숫자 (오른쪽 상단)
	// --------------------------------------------------
	constexpr float kHudIconCenterX = 1510.0f;   // 골드·HP 아이콘 공통 X 위치(둘 다 같은 세로선에 정렬)
	constexpr float kHudTextLeft = 1560.0f;      // 숫자 텍스트 표시 영역 왼쪽 끝
	constexpr float kHudTextRight = 1730.0f;     // 숫자 텍스트 표시 영역 오른쪽 끝
	constexpr float kGoldIconCenterY = 80.0f;    // 골드 아이콘·숫자의 Y 위치
	constexpr float kHpIconCenterY = 140.0f;     // HP 아이콘·숫자의 Y 위치
	constexpr float kHudIconScale = 0.7f;        // 골드/HP 아이콘 크기 배율(둘 다 공유)
	const D2D1::ColorF kHudTextColor = D2D1::ColorF(D2D1::ColorF::White); // 골드/HP 숫자 텍스트 색상

	// --------------------------------------------------
	//  라운드 텍스트 (골드/HP 아래, "라운드 : 현재/총" 한 줄)
	// --------------------------------------------------
	constexpr float kRoundTextCenterY = 200.0f;  // 라운드 텍스트 Y 위치
	// 라벨("라운드 : ")과 숫자("현재/총")를 서로 다른 텍스트로 따로 그린다. 두 X 위치는 서로 독립적이라
	// 하나씩 눈으로 보고 조정하면 됨(라벨 폭이 바뀌어도 숫자 위치는 안 바뀜, 필요하면 같이 옮길 것).
	constexpr float kRoundLabelPosX = 1500.0f;   // 라벨("라운드 : ") 시작 X
	constexpr float kRoundValuePosX = 1620.0f;   // 숫자("현재/총") 시작 X
	constexpr FontSize kRoundTextFontSize = FONT_30; // 라벨/숫자 공통 글자 크기(FONT_12/20/30 중 선택)
	const D2D1::ColorF kRoundLabelColor = D2D1::ColorF(1.0f, 0.55f, 0.0f); // 라벨 색(주황)
	const D2D1::ColorF kRoundValueColor = D2D1::ColorF(D2D1::ColorF::White); // 숫자 색(흰색)
	const wchar_t* const kRoundLabelText = L"라운드 : ";
	const wchar_t* const kRoundValueFormat = L"%d / %d"; // %d=현재 라운드, %d=총 라운드

	// --------------------------------------------------
	//  웨이브 시작 / 디버그 웨이브 조절
	// --------------------------------------------------
	const Vector kStartButtonPos = Vector(1485.0f, 1000.0f); // 웨이브 시작(플레이) 버튼 위치
	constexpr float kStartButtonBaseWidth = 128.0f;  // 버튼 원본 스프라이트 가로(px)
	constexpr float kStartButtonBaseHeight = 129.0f; // 버튼 원본 스프라이트 세로(px)
	constexpr float kPlayButtonScale = 0.6f;         // 플레이 버튼 + 옆 설정 아이콘 공통 크기 배율

	// 설정 아이콘(pause_icon) 표시 위치 — 플레이 버튼(1512.5, 950) 옆에 나란히 배치.
	constexpr float kSettingsIconCenterX = 1575.0f; // 설정 아이콘 X 위치
	constexpr float kSettingsIconCenterY = 1000.0f; // 설정 아이콘 Y 위치

	// 디버그용 라운드 +/- 버튼 (정식 스프라이트 없이 사각형 도형으로 그림). 라운드 텍스트(kRoundTextCenterY=200) 바로 아래, 작게 배치.
	constexpr float kWaveButtonRowY = 245.0f;                            // 라운드 +/- 버튼 Y 위치(라운드 텍스트 아래)
	const Vector kWaveDownButtonPos = Vector(1690.0f, kWaveButtonRowY);  // - 버튼 위치(라운드 라벨 쪽)
	const Vector kWaveUpButtonPos = Vector(1630.0f, kWaveButtonRowY);    // + 버튼 위치(라운드 숫자 쪽)
	const Vector kWaveButtonSize = Vector(28.0f, 28.0f);                 // 두 버튼 공통 크기(기존 40→28로 축소)

	// 골드/HP 디버그 증가(+) 버튼 — 각 숫자 텍스트 오른쪽에 작게 배치.
	const Vector kGoldAddButtonPos = Vector(1680.0f, kGoldIconCenterY); // 골드 + 버튼 위치
	const Vector kHpAddButtonPos = Vector(1650.0f, kHpIconCenterY);     // HP + 버튼 위치
	const Vector kStatAddButtonSize = Vector(26.0f, 26.0f);             // 두 버튼 공통 크기

	// --------------------------------------------------
	//  타워/장애물 상점
	// --------------------------------------------------
	// 타워 상점 버튼: 스크롤 패널(y=270~518) 안 2x2 그리드 위치. 클릭 판정 크기는
	// tower_thumbs_box 배경(renderTowerShopBoxes)과 맞춘다.
	const Vector kDartShopButtonPos = Vector(1520.0f, 332.0f);   // 다트몽키 상점 버튼(좌상단)
	const Vector kTackShopButtonPos = Vector(1680.0f, 332.0f);   // 택슈터 상점 버튼(우상단)
	const Vector kSniperShopButtonPos = Vector(1520.0f, 456.0f); // 스나이퍼몽키 상점 버튼(좌하단)
	const Vector kBombShopButtonPos = Vector(1680.0f, 456.0f);   // 폭탄타워 상점 버튼(우하단)
	const Vector kTowerShopButtonSize = Vector(113.0f, 93.0f);   // 4개 버튼 공통 클릭 판정 크기
	constexpr float kTowerIconScale = 0.7f;                      // 타워 아이콘 자체 크기 배율(드래그 프리뷰에도 사용)

	const Vector kObstacleShopButtonPos = Vector(1675.0f, 1000.0f);  // 장애물 상점 버튼 위치
	const Vector kObstacleShopButtonSize = Vector(109.0f, 113.0f);   // 장애물 상점 버튼 클릭 판정 크기
	constexpr float kObstacleIconScale = 1.0f;                       // 장애물 아이콘 크기 배율(드래그 프리뷰에도 사용)

	// --------------------------------------------------
	//  타워 상점 툴팁 (마우스오버 시 패널) — 1단계: 배경만 표시
	// --------------------------------------------------
	constexpr float kTowerTooltipScaleX = 0.6f; // target_box 가로 배율(기존 1.0에서 0.4만큼 축소)
	constexpr float kTowerTooltipScaleY = 2.4f; // target_box 세로 배율(기존 3.0에서 0.6만큼 축소)
	constexpr float kUpgradeTooltipScaleY = 1.8f; // 업그레이드 버튼 툴팁은 타워 상점 툴팁보다 세로로 짧게.
	constexpr float kTowerTooltipGapX = 15.0f;  // 오른쪽 HUD 패널 왼쪽 끝과 툴팁 사이 간격
	// 채움 사각형은 테두리 스프라이트보다 살짝 작게(테두리 밖으로 삐져나오지 않도록) 축소.
	constexpr float kTowerTooltipFillScaleX = 0.98f;
	constexpr float kTowerTooltipFillScaleY = 0.85f;
	// target_box는 테두리만 있고 안쪽이 투명해서, 스프라이트를 그리기 전에 배경색을 먼저 채운다.
	const D2D1::ColorF kTowerTooltipFillColor = D2D1::ColorF(0.2f, 0.14f, 0.06f, 0.85f); // 진한 갈색, 살짝 반투명

	// 타워 이름/가격/설명 텍스트 레이아웃(패널 안쪽 기준).
	constexpr float kTowerTooltipTextSideGap = 14.0f; // 텍스트 좌우 여백(테두리와 안 겹치게)
	constexpr float kTowerTooltipNameTopGap = 10.0f;  // 이름 텍스트 상단 여백
	constexpr float kTowerTooltipNameHeight = 28.0f;  // 이름 텍스트 한 줄 높이
	constexpr float kTowerTooltipPriceHeight = 26.0f; // 가격 텍스트 한 줄 높이
	constexpr FontSize kTowerTooltipNameFontSize = FONT_20;
	constexpr FontSize kTowerTooltipPriceFontSize = FONT_20;
	constexpr FontSize kTowerTooltipDescFontSize = FONT_20;
	const D2D1::ColorF kTowerTooltipNameColor = D2D1::ColorF(1.0f, 0.85f, 0.1f);  // 이름(노란색)
	const D2D1::ColorF kTowerTooltipPriceColor = D2D1::ColorF(1.0f, 0.85f, 0.1f); // 가격(노란색)
	const D2D1::ColorF kTowerTooltipDescColor = D2D1::ColorF(D2D1::ColorF::White); // 설명(하얀색)
	const wchar_t* const kTowerTooltipPriceFormat = L"%d";

	// --------------------------------------------------
	//  선택된 타워/장애물 패널 (판매/업그레이드)
	// --------------------------------------------------
	// 판매 버튼 배경(sell_box) 가로 스케일. 원본이 288x76로 가로가 길어 오른쪽 UI 패널 폭에
	// 맞추려면 가로만 축소해야 한다. 이 값만 바꾸면 판매 버튼 크기(시각+클릭 판정)가 함께 조절됨.
	constexpr float kSellBoxScaleX = 0.6f;

	const Vector kSellButtonPos = Vector(1600.0f, 920.0f); // 타워 판매 버튼 위치
	const Vector kSellButtonFallbackSize = Vector(109.0f, 60.0f); // sell_box 셀을 못 찾았을 때 대비
	const Vector kUpgradeButtonPos = Vector(1600.0f, 785.0f); // 타워 업그레이드 버튼 위치
	const Vector kUpgradeButtonFallbackSize = Vector(109.0f, 60.0f); // upgrade_box 셀을 못 찾았을 때 대비
	const Vector kObstacleSellButtonPos = Vector(1837.5f, 800.0f); // 장애물 판매 버튼 위치(크기는 kSellBoxScaleX 공유)

	// upgrade_box_buy/cant 배경(284x226, 정사각형에 가까움) 축소 배율.
	// 이 값만 바꾸면 업그레이드 버튼 크기(시각+클릭 판정)가 함께 조절됨. 임시값 — 빌드 후 눈으로 보고 조정할 것.
	constexpr float kUpgradeBoxScale = 0.7f;

	// 타워 이름 아래 등급별 초상화 박스(tower_profile_pic_box, 196x222) 위치·배율.
	// 이름 텍스트(y=520~600)와 업그레이드 박스(y=800) 사이 빈 공간에 배치. 임시값 — 빌드 후 눈으로 보고 조정할 것.
	const Vector kAvatarBoxPos = Vector(1600.0f, 625.0f); // 초상화 박스 위치
	constexpr float kAvatarBoxScale = 0.6f;               // 초상화 박스(프레임) 크기 배율
	constexpr float kAvatarImageScale = 0.5f;             // 박스 안에 그려지는 초상화 이미지 자체 크기 배율(박스보다 작게)

	// 업그레이드 아이콘은 박스 위쪽에, 가격 텍스트는 아래쪽 좁은 띠에.
	constexpr float kUpgradeIconOffsetY = 5.0f;    // 업그레이드 아이콘을 버튼 중심에서 위로 밀어내는 거리
	constexpr float kUpgradeIconScale = 0.9f;        // 업그레이드 아이콘 크기 배율
	constexpr float kUpgradePriceTextHeight = 60.0f; // 버튼 하단에서부터 가격 텍스트가 차지하는 띠 높이
	constexpr float kUpgradeNameTextHeight = 60.0f;  // 버튼 상단에서부터 이름 텍스트가 차지하는 띠 높이

	// 선택 패널 문구 및 이름/레벨 텍스트 표시 영역·색상
	const wchar_t* const kSellTextFormat = L"판매: %d";               // 판매 버튼에 표시되는 판매가 문구
	const wchar_t* const kUpgradeTextFormat = L"%d";                  // 업그레이드 버튼에 표시되는 가격(숫자만)
	const wchar_t* const kUpgradeMaxedText = L"업그레이드 경로 달함"; // 최고 등급 도달 시 업그레이드 버튼 대신 표시
	const wchar_t* const kNameLevelTextFormat = L"%s 레벨 %d";        // 선택한 타워 이름+레벨 문구
	constexpr D2D1_RECT_F kNameLevelTextRect = { 1450.0f, 520.0f, 1740.0f, 600.0f }; // 이름/레벨 텍스트 표시 영역
	const D2D1::ColorF kNameLevelTextColor = D2D1::ColorF(D2D1::ColorF::Yellow);     // 이름/레벨 텍스트 색상

	// --------------------------------------------------
	//  게임오버 팝업
	// --------------------------------------------------
	const Vector kRestartButtonSize = Vector(131.0f, 137.0f); // 재시작 버튼 크기(baked 이미지 원본 크기, 게임 영역 정중앙에 배치)
	const wchar_t* const kGameOverText = L"GAME OVER";                       // 게임오버 문구
	const D2D1::ColorF kGameOverTextColor = D2D1::ColorF(D2D1::ColorF::Red); // 게임오버 문구 색상
	const D2D1::ColorF kGameOverDimColor = D2D1::ColorF(D2D1::ColorF::Black, 0.6f); // 배경 딤(어둡게) 색상/투명도
	constexpr float kGameOverTextTopOffset = -160.0f;    // 문구 표시 영역 위쪽 끝(화면 중앙 기준 오프셋)
	constexpr float kGameOverTextBottomOffset = -80.0f;  // 문구 표시 영역 아래쪽 끝(화면 중앙 기준 오프셋)

	// --------------------------------------------------
	//  설정 팝업 (오륜기 배치)
	// --------------------------------------------------
	// plain_button(131x137) 5개를 오륜기처럼 배치: 위 3개, 아래 2개(위 버튼 사이 아래에 걸치도록).
	// 배열 순서: 0,1,2 = 위쪽 왼→오, 3,4 = 아래쪽 왼→오. 0번(위 왼쪽)이 재개(닫기) 버튼.
	// 위치는 게임 영역 정중앙 기준.
	// 각 버튼 가운데 그려질 아이콘 파일(Resource/Sprite/nukki). 순서: 0 재개, 1 리플레이, 2 자동진행, 3 음악, 4 효과음.
	// 5(홈)은 nukki 개별 파일이 아니라 game_over_popup.xml의 home_icon_shared를 쓰므로 목록에 없음.
	const wchar_t* const kSettingsIconFiles[5] = {
		L"Resource\\Sprite\\nukki\\resume.png",
		L"Resource\\Sprite\\nukki\\replay.png",
		L"Resource\\Sprite\\nukki\\autoplay.png",
		L"Resource\\Sprite\\nukki\\music.png",
		L"Resource\\Sprite\\nukki\\sfx.png",
	};
	constexpr float kSettingsIconScale = 1.0f; // 버튼 안 아이콘 크기 배율. 버튼(plain_button, kSettingsRingScale 적용) 안에 들어오도록 조정.
	constexpr float kSettingsOffMarkScale = 0.25f; // 꺼짐 표시(x.png) 크기 배율. 원본이 커서 축소해서 사용.
	constexpr float kSettingsButtonBaseWidth = 128.0f;  // plain_button 원본 스프라이트 가로 크기(px). 클릭 판정 크기 계산에 사용.
	constexpr float kSettingsButtonBaseHeight = 129.0f; // plain_button 원본 스프라이트 세로 크기(px). 클릭 판정 크기 계산에 사용.
	constexpr float kSettingsRingSpacingX = 250.0f;     // 위쪽 3개 버튼 사이 가로 간격, 아래쪽 2개 버튼 가로 오프셋(간격의 절반)에도 쓰임.
	constexpr float kSettingsRingSpacingY = 200.0f;     // 위쪽 줄과 아래쪽 줄 사이 세로 간격.
	constexpr float kSettingsRingScale = 1.5f;          // 버튼 원본 크기(128x129)에 곱하는 배율 — 실제 그려지는 크기 + 클릭 판정 크기가 함께 커진다.
	constexpr float kSettingsRingCenterOffsetY = -150.0f;  // 5개 버튼 그룹 전체를 위(-)/아래(+)로 한 번에 밀 때 쓰는 값. 게임 영역 정중앙(GameAreaCenterY) 기준.
	const D2D1::ColorF kSettingsDimColor = D2D1::ColorF(D2D1::ColorF::Black, 0.6f); // 설정 팝업 배경 딤(어둡게) 색상/투명도
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
	function<void()> onGoldAdd,
	function<void()> onHpAdd,
	function<void()> onSellClick,
	function<void()> onUpgradeClick,
	function<void()> onObstacleSellClick,
	function<void()> onRestartClick,
	function<void()> onSettingsClick,
	function<void()> onSettingsCloseClick,
	function<void()> onSettingsReplayClick,
	function<void()> onHomeClick,
	function<void(bool)> onAutoPlayToggle)
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

	// 골드/HP 디버그 증가(+) 버튼
	_goldAddButton = createButton(kGoldAddButtonPos, kStatAddButtonSize, onGoldAdd);
	_hpAddButton = createButton(kHpAddButtonPos, kStatAddButtonSize, onHpAdd);

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

	// 설정 팝업 버튼 6개: 3x2 격자 배치. 게임 영역 정중앙 기준.
	const Vector settingsButtonSize(kSettingsButtonBaseWidth * kSettingsRingScale, kSettingsButtonBaseHeight * kSettingsRingScale);
	const Vector ringOffsets[6] = {
		Vector(-kSettingsRingSpacingX, 0.0f),                  // 0: 위 왼쪽
		Vector(0.0f, 0.0f),                                    // 1: 위 가운데
		Vector(kSettingsRingSpacingX, 0.0f),                   // 2: 위 오른쪽
		Vector(-kSettingsRingSpacingX, kSettingsRingSpacingY), // 3: 아래 왼쪽
		Vector(0.0f, kSettingsRingSpacingY),                   // 4: 아래 가운데
		Vector(kSettingsRingSpacingX, kSettingsRingSpacingY),  // 5: 아래 오른쪽
	};
	_settingsOffMarkImg = &res.GetImage(L"Resource\\Sprite\\nukki\\x.png");

	for (int32 i = 0; i < 6; ++i)
	{
		const Vector pos = Vector(static_cast<float>(GWinSizeX) * 0.5f + ringOffsets[i].x, GameAreaCenterY + kSettingsRingCenterOffsetY + ringOffsets[i].y);
		function<void()> onClick;
		if (i == 0)
			onClick = onSettingsCloseClick; // 0번(위 왼쪽) = 재개
		else if (i == 1) // 1번(위 가운데) = 리플레이(게임 재시작)
			onClick = onSettingsReplayClick;
		else if (i == 3) // 3번(음악) — 클릭할 때마다 BGM 음소거 on/off (꺼짐→켜짐 시 처음부터 재생)
			onClick = [this, i]() { _settingsToggleOff[i] = !_settingsToggleOff[i]; AudioManager::GetInstance().SetBgmMuted(_settingsToggleOff[i]); };
		else if (i == 4) // 4번(효과음) — 클릭할 때마다 SFX 음소거 on/off
			onClick = [this, i]() { _settingsToggleOff[i] = !_settingsToggleOff[i]; AudioManager::GetInstance().SetSfxMuted(_settingsToggleOff[i]); };
		else if (i == 2) // 2번(자동진행) — 오디오와 무관, on/off 상태만 토글
			onClick = [this, i, onAutoPlayToggle]()
			{
				_settingsToggleOff[i] = !_settingsToggleOff[i];
				if (onAutoPlayToggle != nullptr)
					onAutoPlayToggle(!_settingsToggleOff[i]); // ToggleOff==false가 "켜짐"
			};
		else if (i == 5) // 5번(홈) — 로비씬으로 이동
			onClick = onHomeClick;
		else
			onClick = []() {};
		_settingsMenuButtons[i] = createButton(pos, settingsButtonSize, onClick);
		_settingsMenuButtons[i]->SetActive(false);
		_settingsMenuButtons[i]->SetIgnoresModalLock(true); // 설정창 자신의 버튼들이라 입력 잠금 대상에서 제외.
		if (i < 5)
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
	int32 hp, int32 gold, bool isWaveActive,
	int32 currentRound, int32 totalRound, bool isSpeedEnabled,
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
	renderRoundText(graphic, currentRound, totalRound);
	renderMiniButton(graphic, _goldAddButton, true);
	renderMiniButton(graphic, _hpAddButton, true);

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

	// 다른 HUD 요소들 위에 그려져야 하므로 맨 마지막에.
	renderTowerTooltip(graphic);
	renderUpgradeTooltip(graphic, selection);
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
		_hudImg->DrawSprite(graphic, kHudIconCenterX, kGoldIconCenterY, *cell, kHudIconScale);

	wchar_t text[32];
	swprintf_s(text, L"%d", gold);

	graphic.DrawString(text, D2D1::RectF(kHudTextLeft, kGoldIconCenterY - 25.0f, kHudTextRight, kGoldIconCenterY + 25.0f),
		FONT_30, kHudTextColor, DWRITE_TEXT_ALIGNMENT_LEADING);
}

void GameSceneUI::renderHpText(Graphic& graphic, int32 hp) const
{
	if (const CellInfo* cell = _hudSprite->GetCell("lives_icon"))
		_hudImg->DrawSprite(graphic, kHudIconCenterX, kHpIconCenterY, *cell, kHudIconScale);

	wchar_t text[32];
	swprintf_s(text, L"%d", hp);

	graphic.DrawString(text, D2D1::RectF(kHudTextLeft, kHpIconCenterY - 25.0f, kHudTextRight, kHpIconCenterY + 25.0f),
		FONT_30, kHudTextColor, DWRITE_TEXT_ALIGNMENT_LEADING);
}

void GameSceneUI::renderRoundText(Graphic& graphic, int32 currentRound, int32 totalRound) const
{
	const float panelRight = static_cast<float>(GameAreaWidth) + kHudPanelWidth;

	// 라벨("라운드 : ")과 숫자("현재/총")를 색을 다르게 하기 위해 텍스트 두 개로 나눠서 그린다.
	graphic.DrawString(kRoundLabelText, D2D1::RectF(kRoundLabelPosX, kRoundTextCenterY - 25.0f, panelRight, kRoundTextCenterY + 25.0f),
		kRoundTextFontSize, kRoundLabelColor, DWRITE_TEXT_ALIGNMENT_LEADING);

	wchar_t valueText[32];
	swprintf_s(valueText, kRoundValueFormat, currentRound, totalRound);
	graphic.DrawString(valueText, D2D1::RectF(kRoundValuePosX, kRoundTextCenterY - 25.0f, panelRight, kRoundTextCenterY + 25.0f),
		kRoundTextFontSize, kRoundValueColor, DWRITE_TEXT_ALIGNMENT_LEADING);
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
	renderMiniButton(graphic, _waveUpButton, true);
	renderMiniButton(graphic, _waveDownButton, false);
}

// 작은 사각형 +/- 버튼(배경 + 기호)을 그린다. 라운드 +/- 버튼과 골드/HP + 버튼이 공용으로 쓴다.
void GameSceneUI::renderMiniButton(Graphic& graphic, UIButton* button, bool isPlus) const
{
	if (button == nullptr)
		return;

	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	if (renderTarget == nullptr)
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

// target_box 배경을 그리고 텍스트 좌표를 반환하는 공용 함수. X는 오른쪽 HUD 패널 왼쪽 고정, Y는 mouseY를 따라간다.
bool GameSceneUI::renderTooltipPanel(Graphic& graphic, float mouseY, float scaleY, TooltipLayout& outLayout) const
{
	const CellInfo* cell = _hudSprite->GetCell("target_box");
	if (cell == nullptr)
		return false;

	// X: 오른쪽 HUD 패널(게임 영역 바로 오른쪽부터 시작) 왼쪽에 살짝 띄워 고정.
	const float centerX = static_cast<float>(GameAreaWidth) - kTowerTooltipGapX - cell->aw * kTowerTooltipScaleX * 0.5f;
	// Y: 마우스 위치를 그대로 따라간다.
	const float centerY = mouseY;

	const float panelWidth = cell->aw * kTowerTooltipScaleX * kTowerTooltipFillScaleX;
	const float panelHeight = cell->ah * scaleY * kTowerTooltipFillScaleY;

	// 테두리 안쪽 투명한 부분을 채울 배경 사각형을 먼저 그린다.
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* fillBrush = graphic.GetBrush(kTowerTooltipFillColor);
	if (renderTarget != nullptr && fillBrush != nullptr)
	{
		const D2D1_RECT_F fillRect = D2D1::RectF(
			centerX - panelWidth * 0.5f, centerY - panelHeight * 0.5f,
			centerX + panelWidth * 0.5f, centerY + panelHeight * 0.5f);
		renderTarget->FillRectangle(fillRect, fillBrush);
	}

	_hudImg->DrawSprite(graphic, centerX, centerY, *cell, kTowerTooltipScaleX, 0.0f, false, scaleY);

	outLayout.textLeft = centerX - panelWidth * 0.5f + kTowerTooltipTextSideGap;
	outLayout.textRight = centerX + panelWidth * 0.5f - kTowerTooltipTextSideGap;
	outLayout.textTop = centerY - panelHeight * 0.5f + kTowerTooltipNameTopGap;
	outLayout.textBottom = centerY + panelHeight * 0.5f - kTowerTooltipTextSideGap;
	return true;
}

// 타워 상점 버튼 4개 중 마우스가 올라간 버튼이 있으면 target_box 패널에 이름/가격/설명을 그린다.
void GameSceneUI::renderTowerTooltip(Graphic& graphic) const
{
	const struct { UIButton* button; TowerType type; } shopEntries[] = {
		{ _dartMonkeyShopButton, TowerType::DartMonkey },
		{ _tackShooterShopButton, TowerType::TackShooter },
		{ _sniperMonkeyShopButton, TowerType::SniperMonkey },
		{ _bombTowerShopButton, TowerType::BombTower },
	};

	const Vector mousePos = InputManager::GetInstance().GetMousePos();

	TowerType hoveredType = TowerType::DartMonkey;
	bool isHovering = false;
	for (const auto& entry : shopEntries)
	{
		if (entry.button != nullptr && entry.button->IsActive() && entry.button->ContainsPoint(mousePos))
		{
			hoveredType = entry.type;
			isHovering = true;
			break;
		}
	}
	if (!isHovering)
		return;

	TooltipLayout layout;
	if (!renderTooltipPanel(graphic, mousePos.y, kTowerTooltipScaleY, layout))
		return;

	// 이름(노란색) → 가격(노란색) → 설명(하얀색) 순서로 위에서부터 채운다.
	const TowerStat& stat = GetTowerStat(hoveredType);
	const float textLeft = layout.textLeft;
	const float textRight = layout.textRight;
	float textTop = layout.textTop;

	graphic.DrawString(stat.name.c_str(), D2D1::RectF(textLeft, textTop, textRight, textTop + kTowerTooltipNameHeight),
		kTowerTooltipNameFontSize, kTowerTooltipNameColor, DWRITE_TEXT_ALIGNMENT_LEADING);
	textTop += kTowerTooltipNameHeight;

	wchar_t priceText[32];
	swprintf_s(priceText, kTowerTooltipPriceFormat, stat.basePrice);
	graphic.DrawString(priceText, D2D1::RectF(textLeft, textTop, textRight, textTop + kTowerTooltipPriceHeight),
		kTowerTooltipPriceFontSize, kTowerTooltipPriceColor, DWRITE_TEXT_ALIGNMENT_LEADING);
	textTop += kTowerTooltipPriceHeight;

	graphic.DrawString(stat.description.c_str(), D2D1::RectF(textLeft, textTop, textRight, layout.textBottom),
		kTowerTooltipDescFontSize, kTowerTooltipDescColor, DWRITE_TEXT_ALIGNMENT_LEADING);
}

// 업그레이드 버튼에 마우스를 올리면 다음 업그레이드 설명을 renderTooltipPanel 공용 패널로 보여준다.
void GameSceneUI::renderUpgradeTooltip(Graphic& graphic, const TowerSelectionInfo& selection) const
{
	if (!selection.canUpgrade || selection.upgradeDescription.empty())
		return;
	if (_upgradeButton == nullptr || !_upgradeButton->IsActive())
		return;

	const Vector mousePos = InputManager::GetInstance().GetMousePos();
	if (!_upgradeButton->ContainsPoint(mousePos))
		return;

	TooltipLayout layout;
	if (!renderTooltipPanel(graphic, mousePos.y, kUpgradeTooltipScaleY, layout))
		return;

	graphic.DrawString(selection.upgradeDescription.c_str(),
		D2D1::RectF(layout.textLeft, layout.textTop, layout.textRight, layout.textBottom),
		kTowerTooltipDescFontSize, kTowerTooltipDescColor, DWRITE_TEXT_ALIGNMENT_LEADING);
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
		// 다음 업그레이드 이름(버튼 상단 좁은 띠).
		if (!selection.upgradeName.empty())
		{
			const Vector pos = _upgradeButton->GetPos();
			const Vector size = _upgradeButton->GetSize();
			graphic.DrawString(selection.upgradeName.c_str(), D2D1::RectF(
				pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
				pos.x + size.x * 0.5f, pos.y - size.y * 0.5f + kUpgradeNameTextHeight),
				FONT_20, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER,
				DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		}

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

	for (int32 i = 0; i < 6; ++i)
	{
		UIButton* button = _settingsMenuButtons[i];
		if (button == nullptr)
			continue;
		const Vector pos = button->GetPos();
		_hudImg->DrawSprite(graphic, pos.x, pos.y, *cell, kSettingsRingScale, 0.0f);

		if (i == 5) // 홈 아이콘은 nukki 개별 PNG가 아니라 game_over_popup.xml의 home_icon_shared 셀.
		{
			if (_popupImg != nullptr && _popupSprite != nullptr)
				if (const CellInfo* homeCell = _popupSprite->GetCell("home_icon_shared"))
					_popupImg->DrawSprite(graphic, pos.x, pos.y, *homeCell, kSettingsIconScale, 0.0f);
		}
		else if (_settingsIconImgs[i] != nullptr)
			_settingsIconImgs[i]->Draw(graphic, pos.x, pos.y, kSettingsIconScale, 0.0f);

		if (_settingsToggleOff[i] && _settingsOffMarkImg != nullptr)
			_settingsOffMarkImg->Draw(graphic, pos.x, pos.y, kSettingsOffMarkScale, 0.0f);
	}
}
