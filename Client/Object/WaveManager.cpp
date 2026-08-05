#include "pch.h"
#include "WaveManager.h"
#include "Bloon.h"
#include "BloonFactory.h"
#include "Scene.h"

void WaveManager::Init(ObjectPool<Bloon>* pool, const Vector& spawnPos, const vector<Vector>* path, Scene* scene)
{
	_pool = pool;
	_spawnPos = spawnPos;
	_path = path;
	_scene = scene;

	_waves = {
		{ { { BloonColor::Red, 2, 1.0f } } },
	};
}

void WaveManager::StartWave(int32 waveIndex)
{
	if (_isActive)
		return;
	if (waveIndex < 0 || waveIndex >= static_cast<int32>(_waves.size()))
		return;

	_isActive = true;
	_waveIndex = waveIndex;
	_entryIndex = 0;
	_spawnedInEntry = 0;
	_spawnTimer = 0.f;

	spawnNext();
}

void WaveManager::Update(float deltaTime)
{
	if (!_isActive)
		return;

	_spawnTimer += deltaTime;

	const SpawnEntry& entry = _waves[_waveIndex].entries[_entryIndex];
	if (_spawnTimer < entry.interval)
		return;

	_spawnTimer -= entry.interval;
	spawnNext();
}

void WaveManager::spawnNext()
{
	SpawnEntry& entry = _waves[_waveIndex].entries[_entryIndex];

	Bloon* bloon = BloonFactory::Create(*_pool, entry.color, _spawnPos, _path);
	if (bloon != nullptr && _scene != nullptr)
		_scene->AddActor(bloon);

	if (++_spawnedInEntry < entry.count)
		return;

	_spawnedInEntry = 0;
	if (++_entryIndex >= static_cast<int32>(_waves[_waveIndex].entries.size()))
		_isActive = false;
}
