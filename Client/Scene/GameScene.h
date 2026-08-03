#pragma once
#include "Scene.h"
#include "Image.h"
#include "Sprite.h"
#include "Grid.h"

class GameScene : public Scene
{
	using Super = Scene;

public :
	GameScene() : Super(SceneType::Game) {}

	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;



private :
	// 디버그용 그리드 선 렌더링. 타일/타워배치 확인용이며 게임 로직에는 아직 관여하지 않는다.
	void renderGrid(Graphic& graphic);

	Image _inGameBg;
	Image _RealGameBG;
	Sprite _sprite;
	Grid _grid;

};

