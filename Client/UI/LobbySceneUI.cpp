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
}

void LobbySceneUI::Init(function<void()> onPlayClick)
{
	ResourceManager& res = ResourceManager::GetInstance();
	_background = &res.GetImage(L"Resource\\Image_png\\lobby_background.png");
	_trophy = &res.GetImage(L"Resource\\Sprite\\nukki\\gold_trophy_nukki.png");

	_playButton = new UIButton();
	_playButton->SetPos(kPlayButtonPos);
	_playButton->SetSize(Vector(kPlayButtonWidth, kPlayButtonHeight));
	_playButton->SetActive(true);
	_playButton->SetOnClick(onPlayClick);
	UIManager::GetInstance().Register(_playButton);
}

void LobbySceneUI::Render(Graphic& graphic) const
{
	// 이미지(1669x942)가 창(1760x1040)보다 작으므로, 창을 완전히 덮도록 스케일을 계산해서 중앙에 그린다.
	const D2D1_SIZE_F bgSize = _background->GetSize();
	const float bgScale = std::max(static_cast<float>(GWinSizeX) / bgSize.width, static_cast<float>(GWinSizeY) / bgSize.height);
	_background->Draw(graphic, static_cast<float>(GWinSizeX) * 0.5f, static_cast<float>(GWinSizeY) * 0.5f, bgScale);

	_trophy->Draw(graphic, static_cast<float>(GWinSizeX) * 0.5f, static_cast<float>(GWinSizeY) * 0.5f, kTrophyScale);

	if (_playButton == nullptr)
		return;

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
