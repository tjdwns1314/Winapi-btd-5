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
#include "DebugOverlay.h"
#include "SaveData.h"

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
	Projectile* SpawnProjectile(const Vector& pos,const Vector& dir, float damage, const string& spriteKey, float speed, float maxDistance, float splashRadius = 0.f, int32 pierceCount = 1);

	void AddDebugCircle(const Vector& pos, float radius, float duration);


	// 체력은 싱글톤이 아니라 GameScene이 소유한다. BloonPopResolver가 새어나감 데미지를 넣을 때 접근한다.
	HealthManager& GetHealthManager() { return _healthManager; }
	// 골드도 마찬가지로 싱글톤이 아니라 GameScene이 소유한다.
	EconomyManager& GetEconomyManager() { return _economyManager; }

	// 저장/불러오기. 웨이브가 Idle 상태일 때만 저장을 허용한다. (로비의 불러오기/새 게임 버튼이 나중에 호출할 API)
	bool CanSave() const { return _waveManager.IsWaveActive() == false; }
	void SaveToFile(const wstring& path) const;
	void LoadFromFile(const wstring& path);

	// 로비의 "게임 재개" 버튼 전용. 저장 파일을 읽어 pending 상태만 만들고 Restart()는 호출하지 않는다.
	// (로비에서는 GameScene::Init()이 이번 세션에 아직 한 번도 안 됐을 수 있어 _graphicRef가 비어 있고,
	//  Restart() 내부에서 세이브 파일을 삭제해버리는 것도 위험하다. 실제 로드 반영은
	//  이후 SceneManager::ChangeScene(Game)이 호출할 Init()에서 일어난다.)
	bool PrepareLoad(const wstring& path);

	// GameScene 자동저장 파일 경로. 로비 UI도 같은 경로를 참조해야 해서 공개해둔다.
	static constexpr wchar_t kSaveFilePath[] = L"Save\\save.json";

protected:
	virtual void CreateUI() override;

private:
	DebugOverlay _debugOverlay;

	// 내부 로직 헬퍼
	void onStartButtonClick();
	float getTimeScale() const;
	void updateDebugWaveTitle();
	SaveData BuildSaveData() const;

	// 게임오버 후 재시작 버튼을 누르면 호출된다. Cleanup() 후 Init()을 다시 실행해 전부 초기화한다.
	void Restart();


private:
	WaveManager _waveManager;
	HealthManager _healthManager;
	EconomyManager _economyManager;
	bool _speedEnabled = false; // 2배속 on/off. 웨이브가 끝나도 리셋하지 않고 유지한다.
	bool _isSettingsOpen = false; // 설정 팝업이 열려 있는 동안 게임 로직 전체를 정지시킨다.
	float _gameOverFadeTimer = 0.0f; // 게임오버 딤 페이드인 경과 시간(초).

	// Init()이 이 값을 보고 새 게임 대신 저장 데이터로 초기화한다. LoadFromFile()이 Restart() 전에 채워 넣는다.
	bool _hasPendingLoad = false;
	SaveData _pendingLoadData;

	// Restart()에서 Init()을 다시 호출하기 위해 보관해둔다. Game이 소유한 Graphic이라 수명은 항상 유효하다.
	Graphic* _graphicRef = nullptr;


	// 스프라이트 및 이미지 리소스
	Image*       _inGameBg           = nullptr;
	SpriteAtlas* _sprite             = nullptr; // InGame.xml

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
