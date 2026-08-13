#include "pch.h"
#include "PoolManager.h"

void PoolManager::Init(size_t bloonSize, size_t projectileSize, size_t towerSize, size_t obstacleSize)
{
	_bloonPool.Init(bloonSize);
	_projectilePool.Init(projectileSize);
	_towerPool.Init(towerSize);
	_obstaclePool.Init(obstacleSize);
}
