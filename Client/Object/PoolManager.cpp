#include "pch.h"
#include "PoolManager.h"

void PoolManager::Init(size_t bloonSize, size_t projectileSize)
{
	_bloonPool.Init(bloonSize);
	_projectilePool.Init(projectileSize);
}
