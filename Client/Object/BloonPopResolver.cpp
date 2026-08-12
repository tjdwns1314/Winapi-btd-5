#include "pch.h"
#include "BloonPopResolver.h"
#include "Bloon.h"
#include "BloonFactory.h"
#include "PoolManager.h"
#include "Scene.h"
#include "GameScene.h"

int32 BloonPopResolver::GetLayerHp(BloonColor color)
{
	return GetBloonStat(color).layerHp;
}

BloonPopResolver::Result BloonPopResolver::resolve(BloonColor color, int32 hp, int32 damage)
{
	Result result;

	hp -= damage;
	if (hp > 0)
	{
		result.popped = false;
		result.remainingHp = hp;
		return result;
	}

	result.popped = true;
	const int32 leftoverDamage = -hp; // 이번 레이어를 죽이고 남은 관통 데미지
	result.totalGoldReward = GetBloonStat(color).goldReward; // 이 레이어 자체가 터진 몫

	const BloonStat& stat = GetBloonStat(color);
	for (const BloonChildSpawn& child : stat.children)
	{
		for (int32 i = 0; i < child.count; ++i)
		{
			const Result childResult = resolve(child.color, GetLayerHp(child.color), leftoverDamage);
			if (childResult.popped)
			{
				// 남은 데미지가 자식까지 죽였다면, 그 자식이 만든 스폰 목록을 그대로 이어붙인다.
				for (const SpawnRequest& spawn : childResult.spawns)
					result.spawns.push_back(spawn);
				result.totalGoldReward += childResult.totalGoldReward; // 자식까지 실제로 터졌을 때만 그만큼 합산
			}
			else
			{
				result.spawns.push_back({ child.color, childResult.remainingHp });
			}
		}
	}

	return result;
}

void BloonPopResolver::HandleHit(Bloon& bloon, float damage)
{
	const Result result = resolve(bloon.GetColor(), bloon.GetHp(), static_cast<int32>(damage));
	if (!result.popped)
	{
		bloon.SetHp(result.remainingHp);
		return;
	}

	bloon.SetPendingKill();

	Scene* owner = bloon.GetOwner();
	if (owner == nullptr)
		return;

	// Bloon은 GameScene에서만 생성되므로 안전하게 다운캐스팅한다.
	GameScene* gameScene = static_cast<GameScene*>(owner);
	gameScene->GetEconomyManager().Add(result.totalGoldReward);

	for (const SpawnRequest& spawn : result.spawns)
	{
		Bloon* child = BloonFactory::Create(PoolManager::GetInstance().GetBloonPool(),
			spawn.color, bloon.GetPos(), bloon.GetPath(), bloon.GetWaypointIndex());
		if (child == nullptr)
			continue;
		child->SetHp(spawn.hp);
		owner->AddActor(child);
	}
}


