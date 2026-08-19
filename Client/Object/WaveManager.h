#pragma once

#include "BloonType.h"

class Bloon;
class Scene;
template<typename T>
class ObjectPool;

// 한 라운드의 스폰 데이터
struct WaveData
{
	vector<BloonColor> spawnOrder;
	float spawnInterval = 0.f;
};

class WaveManager
{
public:
	void Init(ObjectPool<Bloon>* pool, const Vector& spawnPos, const vector<Vector>* path, Scene* scene);

	// 웨이브 진행
	bool StartNextWave();
	void Update(float deltaTime);
	bool IsWaveActive() const { return _state != WaveState::Idle; }

	// 라운드 디버그
	void SetNextRound(int32 roundNumber);
	int32 GetNextRoundNumber() const { return _roundIndex + 1; }
	int32 GetCurrentRoundNumber() const { return IsWaveActive() ? _roundIndex : 0; }
	// HUD 표시용: 진행 중이면 현재 라운드, 대기 중이면 다음에 시작할 라운드.
	int32 GetDisplayRoundNumber() const { return IsWaveActive() ? _roundIndex : GetNextRoundNumber(); }
	int32 GetTotalRoundNumber() const;

private:
	enum class WaveState
	{
		Idle,
		Spawning,
		WaitingClear
	};

	// 라운드 생성
	static WaveData buildRound(int32 roundNumber);

	// 스폰 및 상태 처리
	void spawnNext();
	bool isFieldClear() const;

private:
	// 외부 참조
	ObjectPool<Bloon>* _pool = nullptr;
	const vector<Vector>* _path = nullptr;
	Scene* _scene = nullptr;
	Vector _spawnPos;

	// 웨이브 상태
	WaveState _state = WaveState::Idle;
	int32 _roundIndex = 0;
	WaveData _currentRound;

	// 스폰 진행 상태
	int32 _spawnIndex = 0;
	float _spawnTimer = 0.f;
};