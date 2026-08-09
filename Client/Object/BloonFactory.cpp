#include "pch.h"
#include "BloonFactory.h"
#include "Bloon.h"
#include "ResourceManager.h"

namespace
{
	Image& getBloonImage(const wstring& spriteKey)
	{
		const wstring path = L"Resource\\" + spriteKey + L".png";
		return ResourceManager::GetInstance().GetImage(path.c_str());
	}
}

Bloon* BloonFactory::Create(ObjectPool<Bloon>& pool, BloonColor color, const Vector& pos, const vector<Vector>* path, size_t waypointIndex)
{
	Bloon* bloon = pool.Acquire();
	if (bloon == nullptr)
		return nullptr;

	const BloonStat& stat = GetBloonStat(color);

	bloon->SetColor(color);
	bloon->SetPos(pos);
	bloon->SetPath(path, waypointIndex);
	bloon->SetHp(stat.layerHp);
	bloon->SetMoveSpeed(stat.speed);
	bloon->SetImage(&getBloonImage(stat.spriteKey));
	bloon->Init();
	return bloon;
}
