#include "pch.h"
#include "TowerFactory.h"
#include "Tower.h"
#include "TowerFireBehavior.h"
#include "ResourceManager.h"

Tower* TowerFactory::Create(ObjectPool<Tower>& pool, TowerType type, const Vector& pos)
{
	Tower* tower = pool.Acquire();
	if (tower == nullptr)
		return nullptr;

	const TowerVisual& visual = GetTowerVisual(type);
	ResourceManager& res = ResourceManager::GetInstance();

	tower->SetType(type);
	tower->SetPos(pos);

	if (visual.useBakedImage)
	{
		tower->SetBakedImage(&res.GetImage(visual.bakedImageKey.c_str()));
	}
	else
	{
		tower->SetImage(&res.GetImage(L"Resource\\Sprite\\InGame.png"));
		tower->SetCell(res.GetAtlas(L"Resource\\Sprite\\InGame.xml").GetCell(visual.cellName.c_str()));
	}

	tower->SetTowerData(GetTowerStat(type));
	tower->SetFireBehavior(GetFireBehavior(type));
	tower->SetFrameKeyFn(GetTowerFrameKeyFn(type));

	tower->Init();
	return tower;
}
