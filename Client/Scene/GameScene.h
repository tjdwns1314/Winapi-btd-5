#pragma once
#include "Scene.h"
#include "Image.h"
#include "SpriteAtlas.h"
#include "Grid.h"
#include "TileMap.h"
#include "PathFinder.h"
#include "ResourceManager.h"
#include "BloonFactory.h"


class GameScene : public Scene
{
	using Super = Scene;

public :
	GameScene() : Super(SceneType::Game) {}

	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;



private:
	void renderTileMap(Graphic& graphic);
	void renderGrid(Graphic& graphic);
	void renderStartEndDebug(Graphic& graphic);


	Image * _inGameBg = nullptr;
	Image * _monkeyLaneBg = nullptr;      // 기존 _RealGameBG 대체
	Image * _tile1Img = nullptr;
	SpriteAtlas * _sprite = nullptr;           // InGame.xml
	SpriteAtlas * _monkeyLaneSprite = nullptr; // monkey_lane.xml
	Grid _grid;
	TileMap _tileMap;
	vector<Vector> _path;

};

