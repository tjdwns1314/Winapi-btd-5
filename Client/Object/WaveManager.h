#pragma once
#include "BloonType.h"
class Bloon;
class Scene;
template<typename T> class ObjectPool;

//// 한 라운드 안에서 같은 색상을 연속으로 스폰하는 구간 하나.
//struct WaveSpawnEntry
//{
//	BloonColor color;
//	int32 count;
//	float interval;     // 이 구간 내부, 풍선과 풍선 사이 스폰 간격(초)
//};

// 한 라운드 분량의 스폰 구간 목록. 구간 사이에는 대기 시간 없이 바로 이어서 스폰된다.
struct WaveData
{
	vector<BloonColor> spawnOrder;
	float spawnInterval = 0.f;
};

class WaveManager
{
public:
	void Init(ObjectPool<Bloon>* pool, const Vector& spawnPos, const vector<Vector>* path, Scene* scene);
	bool StartNextWave();
	bool IsWaveActive() const { return _state != WaveState::Idle; }
	void Update(float deltaTime);

	// 디버그용: Idle 상태에서만 다음 시작 라운드를 강제로 지정한다(1~kRoundCount로 clamp).
	void SetNextRound(int32 roundNumber);
	int32 GetNextRoundNumber() const { return _roundIndex + 1; }

	// 현재 진행 중인 라운드 번호. 웨이브가 진행 중이 아니면 0.
	int32 GetCurrentRoundNumber() const { return IsWaveActive() ? _roundIndex : 0; }

private:
	enum class WaveState
	{
		Idle,
		Spawning,
		WaitingClear
	};

	static WaveData buildRound(int32 roundNumber);
	void spawnNext();
	bool isFieldClear() const;

	ObjectPool<Bloon>* _pool = nullptr;
	Vector _spawnPos;
	const vector<Vector>* _path = nullptr;
	Scene* _scene = nullptr;

	WaveState _state = WaveState::Idle;
	int32 _roundIndex = 0;      // 다음에 시작할(혹은 진행 중인) 라운드 번호, 1부터 시작
	WaveData _currentRound;
	int32 _spawnIndex = 0;
	float _spawnTimer = 0.f;
};