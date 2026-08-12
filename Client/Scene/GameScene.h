#pragma once

#include "Scene.h"
#include "Image.h"
#include "SpriteAtlas.h"
#include "Grid.h"
#include "TileMap.h"
#include "PathFinder.h"
#include "ResourceManager.h"
#include "BloonFactory.h"
#include "GameSceneUI.h"
#include "Bloon.h"
#include "WaveManager.h"
#include "ProjectileFactory.h"
#include "Projectile.h"
#include "TowerType.h"
#include "HealthManager.h"
#include "EconomyManager.h"

class Tower;

class GameScene : public Scene
{
	using Super = Scene;

public:
	GameScene() : Super(SceneType::Game) {}

	// --------------------------------------------------
	//  주요 생명주기 (Lifecycle)
	// --------------------------------------------------
	virtual void Init(Graphic& graphic) override;
	virtual void Cleanup() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;

	// --------------------------------------------------
	//  오브젝트 스폰 대행
	// --------------------------------------------------
	// Tower가 풀/Scene 등록을 직접 몰라도 되도록, 발사만 대행해준다.
	Projectile* SpawnProjectile(const Vector& pos,
		const Vector& dir, float damage, const string& spriteKey, float speed);

	// 체력은 싱글톤이 아니라 GameScene이 소유한다. BloonPopResolver가 새어나감 데미지를 넣을 때 접근한다.
	HealthManager& GetHealthManager() { return _healthManager; }
	// 골드도 마찬가지로 싱글톤이 아니라 GameScene이 소유한다.
	EconomyManager& GetEconomyManager() { return _economyManager; }

protected:
	virtual void CreateUI() override;

private:
	// 디버그 & 맵 렌더링 헬퍼
	void renderTileMap(Graphic& graphic);
	void renderGrid(Graphic& graphic);
	void renderStartEndDebug(Graphic& graphic);
	void renderPathDebug(Graphic& graphic);

	// 내부 로직 헬퍼
	void updateTowerDrag();
	void updateDebugWaveTitle();
	void tryStartTowerDrag(TowerType type);

	void updateTowerSelect();
	void sellSelectedTower();
	void upgradeSelectedTower();


private:
	WaveManager _waveManager;
	HealthManager _healthManager;
	EconomyManager _economyManager;

	// 스프라이트 및 이미지 리소스
	Image*       _inGameBg           = nullptr;
	Image*       _monkeyLaneBg       = nullptr; // 기존 _RealGameBG 대체
	Image*       _tile1Img           = nullptr;
	Image*       _tile2Img           = nullptr;
	Image*       _hudImg             = nullptr; // in_game_hud.png (시험용)
	Image*       _blueImg            = nullptr; // [임시 테스트] Blue.png
	SpriteAtlas* _sprite             = nullptr; // InGame.xml
	SpriteAtlas* _monkeyLaneSprite   = nullptr; // monkey_lane.xml
	SpriteAtlas* _hudSprite          = nullptr; // in_game_hud.xml (시험용)

	// 맵 / 경로 데이터
	Grid           _grid;
	TileMap        _tileMap;
	vector<Vector> _path;
	Vector         _bloonSpawnPos;

	// UI 및 타워 드래그 상태
	GameSceneUI _ui;
	bool _isDraggingTower = false;
	TowerType _draggingTowerType = TowerType::DartMonkey;
	Tower* _selectedTower = nullptr;

	// 디버그 타이틀바 표시용 캐시 (값이 바뀔 때만 SetWindowText 호출)
	int32 _lastTitleCurrentRound = -1;
	int32 _lastTitleNextRound    = -1;
};

