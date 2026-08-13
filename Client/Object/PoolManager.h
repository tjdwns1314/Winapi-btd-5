#pragma once
#include "Singleton.h"
#include "ObjectPool.h"
#include "Bloon.h"
#include "Projectile.h"
#include "Tower.h"
#include "Obstacle.h"
class PoolManager : public Singleton<PoolManager>
{
	friend Singleton<PoolManager>;

public:
	void Init(size_t bloonSize, size_t projectileSize, size_t towerSize, size_t obstacleSize);
	ObjectPool<Bloon>& GetBloonPool() { return _bloonPool; }
	ObjectPool<Projectile>& GetProjectilePool() { return _projectilePool; }
	ObjectPool<Tower>& GetTowerPool() { return _towerPool; }
	ObjectPool<Obstacle>& GetObstaclePool() { return _obstaclePool; }

private:
	PoolManager() = default;
	~PoolManager() = default;

	ObjectPool<Bloon> _bloonPool;
	ObjectPool<Projectile> _projectilePool;
	ObjectPool<Tower> _towerPool;
	ObjectPool<Obstacle> _obstaclePool;
};

