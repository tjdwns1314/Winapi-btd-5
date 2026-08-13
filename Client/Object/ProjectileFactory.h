#pragma once
#include "ObjectPool.h"

class Projectile;

// Projectile 생성 + 초기화(위치/방향/데미지 조립)를 한 곳에 모은다.
// Scene 등록은 호출부 책임.
class ProjectileFactory
{
public:
	static Projectile* Create(ObjectPool<Projectile>& pool,
		const Vector& pos, const Vector& dir, float damage,
		const string& spriteKey, float speed, float splashRadius = 0.f, int32 pierceCount = 1);
};
