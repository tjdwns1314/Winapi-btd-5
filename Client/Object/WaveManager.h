#pragma once
#include "BloonType.h"
class Bloon;
class Scene;
template<typename T> class ObjectPool;
class WaveManager
{
public:
	void Init(ObjectPool<Bloon>* pool, const Vector& spawnPos, const vector<Vector>* path, Scene* scene);
	void StartWave(int32 waveIndex);
	void Update(float deltaTime);

	bool IsWaveActive() const { return _isActive; }


private:
	struct SpawnEntry { BloonColor color; int32 count; float interval; };
	struct WaveData { vector<SpawnEntry> entries; };
	void spawnNext();
private:
	vector<WaveData> _waves;

	ObjectPool<Bloon>* _pool = nullptr;
	Vector _spawnPos;
	const vector<Vector>* _path = nullptr;
	Scene* _scene = nullptr;

	bool _isActive = false;
	int32 _waveIndex = 0;
	int32 _entryIndex = 0;
	int32 _spawnedInEntry = 0;
	float _spawnTimer = 0.f;
};
