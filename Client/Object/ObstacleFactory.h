#pragma once
#include "ObstacleType.h"
#include "ObjectPool.h"

class Obstacle;

class ObstacleFactory
{
public:
	static Obstacle* Create(ObjectPool<Obstacle>& pool, ObstacleType type, const Vector& pos);
};
