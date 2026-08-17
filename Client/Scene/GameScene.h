#pragma once

#include "Scene.h"
#include "Image.h"
#include "SpriteAtlas.h"
#include "MapSystem.h"
#include "ResourceManager.h"
#include "BloonFactory.h"
#include "GameSceneUI.h"
#include "Bloon.h"
#include "WaveManager.h"
#include "ProjectileFactory.h"
#include "Projectile.h"
#include "TowerType.h"
#include "TowerController.h"
#include "ObstacleType.h"
#include "ObstacleController.h"
#include "HealthManager.h"
#include "EconomyManager.h"

class Tower;
class Obstacle;

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
	Projectile* SpawnProjectile(const Vector& pos,const Vector& dir, float damage, const string& spriteKey, float speed, float splashRadius = 0.f, int32 pierceCount = 1);

	void AddDebugCircle(const Vector& pos, float radius, float duration);


	// 체력은 싱글톤이 아니라 GameScene이 소유한다. BloonPopResolver가 새어나감 데미지를 넣을 때 접근한다.
	HealthManager& GetHealthManager() { return _healthManager; }
	// 골드도 마찬가지로 싱글톤이 아니라 GameScene이 소유한다.
	EconomyManager& GetEconomyManager() { return _economyManager; }

protected:
	virtual void CreateUI() override;

private:
	// 디버그 서클 렌더 헬퍼
	void renderDebugCircles(Graphic& graphic);
	// 풍선 콜라이더 범위 디버그 렌더 헬퍼
	void renderColliderDebug(Graphic& graphic);

	struct DebugCircle
	{
		Vector pos;
		float radius;
		float remaining;
	};
	vector<DebugCircle> _debugCircles;



	// 내부 로직 헬퍼
	void onStartButtonClick();
	float getTimeScale() const;
	void updateDebugWaveTitle();

	// 게임오버 후 재시작 버튼을 누르면 호출된다. Cleanup() 후 Init()을 다시 실행해 전부 초기화한다.
	void Restart();


private:
	WaveManager _waveManager;
	HealthManager _healthManager;
	EconomyManager _economyManager;
	bool _speedEnabled = false; // 2배속 on/off. 웨이브가 끝나도 리셋하지 않고 유지한다.
	bool _debugOverlayEnabled = false; // F2로 그리드/경로/시작-끝/풍선 콜라이더 디버그 표시 on/off.

	// Restart()에서 Init()을 다시 호출하기 위해 보관해둔다. Game이 소유한 Graphic이라 수명은 항상 유효하다.
	Graphic* _graphicRef = nullptr;


	// 스프라이트 및 이미지 리소스
	Image*       _inGameBg           = nullptr;
	Image*       _monkeyLaneBg       = nullptr; // 기존 _RealGameBG 대체
	SpriteAtlas* _sprite             = nullptr; // InGame.xml
	SpriteAtlas* _monkeyLaneSprite   = nullptr; // monkey_lane.xml

	// 맵 / 경로
	MapSystem _map;

	// UI 및 타워/장애물 컨트롤러
	GameSceneUI _ui;
	TowerController _towerController;
	ObstacleController _obstacleController;

	// 디버그 타이틀바 표시용 캐시 (값이 바뀔 때만 SetWindowText 호출)
	int32 _lastTitleCurrentRound = -1;
	int32 _lastTitleNextRound    = -1;
};
