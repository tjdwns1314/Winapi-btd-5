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
#include "Bloon.h"
#include "WaveManager.h"
#include "ProjectileFactory.h"
#include "Projectile.h"


class GameScene : public Scene
{
	using Super = Scene;

public :
	GameScene() : Super(SceneType::Game) {}

	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;

	// Tower가 풀/Scene 등록을 직접 몰라도 되도록, 발사만 대행해준다.
	Projectile* SpawnProjectile(const Vector& pos, const Vector& dir, float damage);

private:
	void renderTileMap(Graphic& graphic);
	void renderGrid(Graphic& graphic);
	void renderStartEndDebug(Graphic& graphic);
	void renderPathDebug(Graphic& graphic);

	void renderStartButton(Graphic& graphic);

	ObjectPool<Bloon> _bloonPool;
	ObjectPool<Projectile> _projectilePool;
	WaveManager _waveManager;

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
	Vector _bloonSpawnPos;



};

