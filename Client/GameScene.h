#pragma once
#include "Image.h"
#include "Sprite.h"
class GameScene
{
public :
	void Init(Graphic& graphic);
	void Render(Graphic& graphic);
	void Release();
	void Update();
private :
	Image _inGameBg;
	Sprite _sprite;
};

