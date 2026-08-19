#pragma once

#include "UIButton.h"

class Graphic;
class Image;

// LobbyScene 전용 UI(배경, 트로피 장식, 플레이 버튼)의 생성/배치/렌더링을 전담한다.
// LobbyScene은 콜백만 넘기고 결과를 그리게 시킨다. (GameScene <-> GameSceneUI와 동일한 구조)
class LobbySceneUI
{
public:
	void Init(function<void()> onPlayClick);
	void Render(Graphic& graphic) const;

private:
	UIButton* _playButton = nullptr;

	Image* _background = nullptr; // lobby_background.png
	Image* _trophy = nullptr;     // gold_trophy_nukki.png
};
