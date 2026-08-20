#pragma once

#include "UIButton.h"

class Graphic;
class Image;
class SpriteAtlas;

// LobbyScene 전용 UI(배경, 트로피 장식, 플레이 버튼, 새 게임/게임 재개 선택 팝업)의
// 생성/배치/렌더링을 전담한다.
// LobbyScene은 콜백만 넘기고 결과를 그리게 시킨다. (GameScene <-> GameSceneUI와 동일한 구조)
class LobbySceneUI
{
public:
	void Init(function<void()> onNewGameClick, function<void()> onResumeClick, function<bool()> hasSaveFile);
	void Render(Graphic& graphic) const;

private:
	void openSelectPopup();
	void closeSelectPopup();
	void renderSelectPopup(Graphic& graphic) const;

	UIButton* _playButton = nullptr;

	// "게임 선택하기" 팝업: 새 게임 / 게임 재개 / 닫기(X)
	bool _isSelectOpen = false;
	UIButton* _newGameButton = nullptr;
	UIButton* _resumeButton = nullptr;
	UIButton* _closeButton = nullptr;
	function<bool()> _hasSaveFile; // 세이브 파일 존재 여부. LobbyScene이 넘겨준다(UI가 SaveManager/GameScene을 직접 모름).
	bool _saveExists = false;      // 팝업 열 때마다 _hasSaveFile()로 갱신. false면 "게임 재개" 버튼을 비활성 원으로 덮어 그림.

	Image* _background = nullptr; // lobby_background.png
	Image* _trophy = nullptr;     // gold_trophy_nukki.png

	// 팝업 배경(plain_button)/닫기(close_button) 스프라이트, 버튼 아이콘
	Image* _hudImg = nullptr;          // in_game_hud.png
	SpriteAtlas* _hudSprite = nullptr; // in_game_hud.xml
	Image* _newGameIcon = nullptr;     // nukki/resume.png (재생 아이콘 — "새 게임" 버튼용)
	Image* _resumeIcon = nullptr;      // nukki/save.png (플로피 디스크 아이콘 — "게임 재개" 버튼용)
};
