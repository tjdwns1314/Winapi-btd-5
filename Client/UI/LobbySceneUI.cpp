#include "pch.h"
#include "LobbySceneUI.h"
#include "UIManager.h"
#include "Graphic.h"
#include "ResourceManager.h"

namespace
{
	constexpr float kPlayButtonOffsetY = -10.0f; // 화면 정중앙 기준 Y 오프셋(+아래로, -위로) — 트로피 밑에 오도록 조정
	const Vector kPlayButtonPos = Vector(static_cast<float>(GWinSizeX) * 0.5f, static_cast<float>(GWinSizeY) * 0.5f + kPlayButtonOffsetY); // 플레이 버튼 위치
	constexpr float kPlayButtonWidth = 330.0f;   // 플레이 버튼 가로 크기
	constexpr float kPlayButtonHeight = 70.0f;  // 플레이 버튼 세로 크기
	constexpr FontSize kPlayTextFontSize = FONT_40; // "플레이" 글꼴 크기
	constexpr float kPlayButtonBgAlpha = 0.2f;   // 버튼 배경 반투명 검정 알파값
	const wchar_t* const kPlayButtonText = L"플레이";
	constexpr float kTrophyScale = 0.4f; // 원본 1432x1098로 커서 축소 배율 (미검증 - 실제 비율 확인 후 조정 필요)

	// 새 게임 / 게임 재개 선택 팝업
	const D2D1::ColorF kSelectDimColor = D2D1::ColorF(D2D1::ColorF::Black, 0.6f); // 배경 페이드(딤) 색상/투명도
	const D2D1::ColorF kSelectBlueTextColor = D2D1::ColorF(0.22f, 0.55f, 0.92f); // "게임 선택하기"/버튼 라벨 파란색 (미검증 - 실제 톤은 빌드 후 조정 필요)

	constexpr float kSelectButtonBaseWidth = 131.0f;  // plain_button 원본 스프라이트 가로 크기(px)
	constexpr float kSelectButtonBaseHeight = 137.0f; // plain_button 원본 스프라이트 세로 크기(px)
	constexpr float kSelectButtonScale = 1.6f;        // 버튼 확대 배율(그려지는 크기 + 클릭 판정 크기에 함께 적용)
	constexpr float kSelectButtonSpacingX = 220.0f;   // 화면 중앙에서 두 버튼이 좌우로 각각 떨어지는 거리
	constexpr float kSelectIconScale = 0.9f;          // 버튼 안 아이콘 크기 배율
	const D2D1::ColorF kSelectDisabledDimColor = D2D1::ColorF(D2D1::ColorF::Black, 0.55f); // 세이브 없을 때 "게임 재개" 버튼을 덮는 비활성 원 색상/투명도

	constexpr float kSelectTitleTopOffset = -260.0f;  // "게임 선택하기" 텍스트, 화면 중앙 기준 Y 오프셋
	constexpr FontSize kSelectTitleFontSize = FONT_40;
	const wchar_t* const kSelectTitleText = L"게임 선택하기";

	constexpr float kSelectLabelTopOffset = 110.0f; // 버튼 아래 라벨 텍스트, 버튼 중심 기준 Y 오프셋
	constexpr FontSize kSelectLabelFontSize = FONT_30;
	const wchar_t* const kNewGameText = L"새 게임";
	const wchar_t* const kResumeText = L"게임 재개";

	const Vector kCloseButtonPos = Vector(70.0f, 70.0f); // 화면 왼쪽 위
}

void LobbySceneUI::Init(function<void()> onNewGameClick, function<void()> onResumeClick, function<bool()> hasSaveFile)
{
	ResourceManager& res = ResourceManager::GetInstance();
	_background = &res.GetImage(L"Resource\\Image_png\\lobby_background.png");
	_trophy = &res.GetImage(L"Resource\\Sprite\\nukki\\gold_trophy_nukki.png");

	_hasSaveFile = hasSaveFile;

	_hudImg = &res.GetImage(L"Resource\\Sprite\\in_game_hud.png");
	_hudSprite = &res.GetAtlas(L"Resource\\Sprite\\in_game_hud.xml");
	_newGameIcon = &res.GetImage(L"Resource\\Sprite\\nukki\\resume.png");
	_resumeIcon = &res.GetImage(L"Resource\\Sprite\\nukki\\save.png");

	_playButton = new UIButton();
	_playButton->SetPos(kPlayButtonPos);
	_playButton->SetSize(Vector(kPlayButtonWidth, kPlayButtonHeight));
	_playButton->SetActive(true);
	_playButton->SetOnClick([this]() { openSelectPopup(); });
	UIManager::GetInstance().Register(_playButton);

	const Vector center(static_cast<float>(GWinSizeX) * 0.5f, static_cast<float>(GWinSizeY) * 0.5f);
	const Vector selectButtonSize(kSelectButtonBaseWidth * kSelectButtonScale, kSelectButtonBaseHeight * kSelectButtonScale);

	_newGameButton = new UIButton();
	_newGameButton->SetPos(Vector(center.x - kSelectButtonSpacingX, center.y));
	_newGameButton->SetSize(selectButtonSize);
	_newGameButton->SetActive(false);
	_newGameButton->SetOnClick(onNewGameClick);
	UIManager::GetInstance().Register(_newGameButton);

	_resumeButton = new UIButton();
	_resumeButton->SetPos(Vector(center.x + kSelectButtonSpacingX, center.y));
	_resumeButton->SetSize(selectButtonSize);
	_resumeButton->SetActive(false);
	_resumeButton->SetOnClick(onResumeClick);
	UIManager::GetInstance().Register(_resumeButton);

	_closeButton = new UIButton();
	_closeButton->SetPos(kCloseButtonPos);
	if (const CellInfo* cell = _hudSprite->GetCell("close_button"))
		_closeButton->SetSize(Vector(static_cast<float>(cell->aw), static_cast<float>(cell->ah)));
	_closeButton->SetActive(false);
	_closeButton->SetOnClick([this]() { closeSelectPopup(); });
	UIManager::GetInstance().Register(_closeButton);
}

void LobbySceneUI::openSelectPopup()
{
	_isSelectOpen = true;
	_saveExists = (_hasSaveFile != nullptr) && _hasSaveFile();
	if (_playButton != nullptr) _playButton->SetActive(false);
	if (_newGameButton != nullptr) _newGameButton->SetActive(true);
	if (_resumeButton != nullptr) _resumeButton->SetActive(_saveExists); // 세이브 없으면 클릭 자체를 막는다.
	if (_closeButton != nullptr) _closeButton->SetActive(true);
}

void LobbySceneUI::closeSelectPopup()
{
	_isSelectOpen = false;
	if (_playButton != nullptr) _playButton->SetActive(true);
	if (_newGameButton != nullptr) _newGameButton->SetActive(false);
	if (_resumeButton != nullptr) _resumeButton->SetActive(false);
	if (_closeButton != nullptr) _closeButton->SetActive(false);
}

void LobbySceneUI::Render(Graphic& graphic) const
{
	// 이미지(1669x942)가 창(1760x1040)보다 작으므로, 창을 완전히 덮도록 스케일을 계산해서 중앙에 그린다.
	const D2D1_SIZE_F bgSize = _background->GetSize();
	const float bgScale = std::max(static_cast<float>(GWinSizeX) / bgSize.width, static_cast<float>(GWinSizeY) / bgSize.height);
	_background->Draw(graphic, static_cast<float>(GWinSizeX) * 0.5f, static_cast<float>(GWinSizeY) * 0.5f, bgScale);

	_trophy->Draw(graphic, static_cast<float>(GWinSizeX) * 0.5f, static_cast<float>(GWinSizeY) * 0.5f, kTrophyScale);

	if (_isSelectOpen == false && _playButton != nullptr)
	{
		const Vector pos = _playButton->GetPos();
		const Vector size = _playButton->GetSize();

		const D2D1_RECT_F rect = D2D1::RectF(
			pos.x - size.x * 0.5f, pos.y - size.y * 0.5f,
			pos.x + size.x * 0.5f, pos.y + size.y * 0.5f);

		ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
		ID2D1SolidColorBrush* bgBrush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Black, kPlayButtonBgAlpha));
		if (renderTarget != nullptr && bgBrush != nullptr)
			renderTarget->FillRectangle(rect, bgBrush);

		graphic.DrawString(kPlayButtonText, rect,
			kPlayTextFontSize, D2D1::ColorF(D2D1::ColorF::White), DWRITE_TEXT_ALIGNMENT_CENTER,
			DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	if (_isSelectOpen)
		renderSelectPopup(graphic);
}

void LobbySceneUI::renderSelectPopup(Graphic& graphic) const
{
	// 배경 페이드
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* dimBrush = graphic.GetBrush(kSelectDimColor);
	if (renderTarget != nullptr && dimBrush != nullptr)
		renderTarget->FillRectangle(D2D1::RectF(0.0f, 0.0f,
			static_cast<float>(GWinSizeX), static_cast<float>(GWinSizeY)), dimBrush);

	const float centerY = static_cast<float>(GWinSizeY) * 0.5f;

	graphic.DrawString(kSelectTitleText,
		D2D1::RectF(0.0f, centerY + kSelectTitleTopOffset - 40.0f, static_cast<float>(GWinSizeX), centerY + kSelectTitleTopOffset + 40.0f),
		kSelectTitleFontSize, kSelectBlueTextColor, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	const CellInfo* buttonCell = _hudSprite->GetCell("plain_button");

	struct Entry { UIButton* button; Image* icon; const wchar_t* label; bool disabled; };
	const Entry entries[2] = {
		{ _newGameButton, _newGameIcon, kNewGameText, false },
		{ _resumeButton, _resumeIcon, kResumeText, _saveExists == false },
	};

	for (const Entry& entry : entries)
	{
		if (entry.button == nullptr)
			continue;
		const Vector pos = entry.button->GetPos();

		if (buttonCell != nullptr)
			_hudImg->DrawSprite(graphic, pos.x, pos.y, *buttonCell, kSelectButtonScale, 0.0f);
		if (entry.icon != nullptr)
			entry.icon->Draw(graphic, pos.x, pos.y, kSelectIconScale, 0.0f);

		// 세이브 파일이 없어 "게임 재개"가 비활성 상태면, plain_button 크기만큼 반투명 검정 원을 덮어
		// 비활성화된 것처럼 보이게 한다. 클릭도 openSelectPopup()에서 이미 SetActive(false)로 막아둔 상태.
		if (entry.disabled && renderTarget != nullptr)
		{
			ID2D1SolidColorBrush* disabledBrush = graphic.GetBrush(kSelectDisabledDimColor);
			if (disabledBrush != nullptr)
			{
				const float radiusX = kSelectButtonBaseWidth * kSelectButtonScale * 0.5f;
				const float radiusY = kSelectButtonBaseHeight * kSelectButtonScale * 0.5f;
				renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), radiusX, radiusY), disabledBrush);
			}
		}

		graphic.DrawString(entry.label,
			D2D1::RectF(pos.x - 100.0f, pos.y + kSelectLabelTopOffset - 30.0f, pos.x + 100.0f, pos.y + kSelectLabelTopOffset + 30.0f),
			kSelectLabelFontSize, kSelectBlueTextColor, DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	if (_closeButton != nullptr)
	{
		const Vector pos = _closeButton->GetPos();
		if (const CellInfo* closeCell = _hudSprite->GetCell("close_button"))
			_hudImg->DrawSprite(graphic, pos.x, pos.y, *closeCell, 1.0f, 0.0f);
	}
}
