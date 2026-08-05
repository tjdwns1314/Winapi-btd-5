#pragma once
#include "Scene.h"
#include "Image.h"
#include "SpriteAtlas.h"
#include "Grid.h"
#include "TileMap.h"
#include "PathFinder.h"
#include "ResourceManager.h"
#include "BloonFactory.h"
#include "UIButton.h"


class GameScene : public Scene
{
	using Super = Scene;

public :
	GameScene() : Super(SceneType::Game) {}

	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;

	// 사거리 탐색 등에서 특정 레이어 액터 목록을 읽기 전용으로 조회할 때 사용한다.
	const vector<Actor*>& GetActors(RenderLayer layer) const { return _actors[static_cast<int32>(layer)]; }

private:
	void renderTileMap(Graphic& graphic);
	void renderGrid(Graphic& graphic);
	void renderStartEndDebug(Graphic& graphic);
	void renderPathDebug(Graphic& graphic);

	void renderStartButton(Graphic& graphic);
	void startWave();

	ObjectPool<Bloon> _bloonPool;


	Image * _inGameBg = nullptr;
	Image * _monkeyLaneBg = nullptr;      // 기존 _RealGameBG 대체
	Image * _tile1Img = nullptr;
	Image * _hudImg = nullptr;            // in_game_hud.png (시험용)
	SpriteAtlas * _sprite = nullptr;           // InGame.xml
	SpriteAtlas * _monkeyLaneSprite = nullptr; // monkey_lane.xml
	SpriteAtlas * _hudSprite = nullptr;   // in_game_hud.xml (시험용)
	Grid _grid;
	TileMap _tileMap;
	vector<Vector> _path;


	UIButton _startButton;
	bool _isStarted = false;
	Vector _bloonSpawnPos;

};

