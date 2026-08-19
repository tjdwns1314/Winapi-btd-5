#include "pch.h"
#include "ProjectileFactory.h"
#include "Projectile.h"

Projectile* ProjectileFactory::Create(ObjectPool<Projectile>& pool,
	const Vector& pos, const Vector& dir, float damage, const string& spriteKey, float speed, float maxDistance, float splashRadius, int32 pierceCount)
{
	Projectile* projectile = pool.Acquire();
	if (projectile == nullptr)
		return nullptr;

	projectile->SetPos(pos);
	projectile->SetDir(dir);
	projectile->SetDamage(damage);
	projectile->SetSpriteKey(spriteKey);
	projectile->SetProjectileSpeed(speed);
	projectile->SetMaxDistance(maxDistance);
	projectile->SetSplashRadius(splashRadius);
	projectile->SetPierceCount(pierceCount);
	projectile->Init();
	return projectile;
}
