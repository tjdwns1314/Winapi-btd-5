#include "pch.h"
#include "ObstacleFactory.h"
#include "Obstacle.h"
#include "ResourceManager.h"

Obstacle* ObstacleFactory::Create(ObjectPool<Obstacle>& pool, ObstacleType type, const Vector& pos)
{
	Obstacle* obstacle = pool.Acquire();
	if (obstacle == nullptr)
		return nullptr;

	const ObstacleStat& stat = GetObstacleStat(type);
	ResourceManager& res = ResourceManager::GetInstance();

	obstacle->SetType(type);
	obstacle->SetPos(pos);
	obstacle->SetScale(Vector(stat.renderScale, stat.renderScale));
	obstacle->SetImage(&res.GetImage(L"Resource\\Sprite\\InGame.png"));
	obstacle->SetCell(res.GetAtlas(L"Resource\\Sprite\\InGame.xml").GetCell(stat.cellName.c_str()));

	obstacle->Init();
	return obstacle;
}
