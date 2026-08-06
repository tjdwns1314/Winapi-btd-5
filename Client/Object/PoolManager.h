#pragma once
#include "Singleton.h"
#include "ObjectPool.h"
#include "Bloon.h"
#include "Projectile.h"
class PoolManager : public Singleton<PoolManager>
{
	friend Singleton<PoolManager>;

public:
	void Init(size_t bloonSize, size_t projectileSize);
	ObjectPool<Bloon>& GetBloonPool() { return _bloonPool; }
	ObjectPool<Projectile>& GetProjectilePool() { return _projectilePool; }

private:
	PoolManager() = default;
	~PoolManager() = default;

	ObjectPool<Bloon> _bloonPool;
	ObjectPool<Projectile> _projectilePool;
};

