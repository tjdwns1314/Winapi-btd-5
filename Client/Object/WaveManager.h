#pragma once
#include "BloonType.h"
class Bloon;
class Scene;
template<typename T> class ObjectPool;

struct WaveSpawnEntry { 
	BloonColor color;
	int32 count;
	float interval;
};

struct WaveData
{
	int32 round;
	vector<WaveSpawnEntry> entries;
};


class WaveManager
{
public:
	void Init(ObjectPool<Bloon>* pool, const Vector& spawnPos, const vector<Vector>* path, Scene* scene);
	//void StartWave(int32 waveIndex);
	bool StartNextWave();
	bool IsWaveActive() const { return _state != WaveState::Idle; }
	void Update(float deltaTime);

private:
	enum class WaveState
	{
		Idle,
		Spawning,
		WaitingClear
	};
	struct SpawnEntry { BloonColor color; int32 count; float interval; };
	struct WaveData { vector<SpawnEntry> entries; };
	void spawnNext();

	bool isFieldClear() const;

	vector<WaveData> _waves;

	ObjectPool<Bloon>* _pool = nullptr;
	Vector _spawnPos;
	const vector<Vector>* _path = nullptr;
	Scene* _scene = nullptr;

	WaveState _state = WaveState::Idle;
	int32 _waveIndex = -1;
	int32 _entryIndex = 0;
	int32 _spawnedInEntry = 0;
	float _spawnTimer = 0.f;
	bool _waveClearFlag = false;
};
