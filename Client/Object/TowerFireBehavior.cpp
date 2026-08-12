#include "pch.h"
#include "TowerFireBehavior.h"
#include "Tower.h"
#include "GameScene.h"

namespace
{
	// 다트원숭이 등: 타겟 하나를 추적해서 그 방향으로 1발 발사.
	void fireSingleTarget(Tower& tower)
	{
		Bloon* target = tower.GetTarget();
		if (target == nullptr)
			return;

		GameScene* owner = tower.GetGameScene();
		if (owner == nullptr)
			return;

		Vector dir = target->GetPos() - tower.GetPos();
		if (dir.Length() < SMALL_NUMBER)
			return;

		dir.Normalize();
		owner->SpawnProjectile(tower.GetPos(), dir, static_cast<float>(tower.GetStat().damage), tower.GetStat().projectileKey);
	}

	// 압정슈터: 사거리 안에 적이 있을 때만 8방향으로 동시에 발사. 방향 자체는 타겟을 따라가지 않는다.
	void fireEightDirections(Tower& tower)
	{
		if (tower.GetTarget() == nullptr)
			return;

		GameScene* owner = tower.GetGameScene();
		if (owner == nullptr)
			return;

		constexpr int32 directionCount = 8;
		for (int32 i = 0; i < directionCount; ++i)
		{
			const float rad = DegreeToRadian(360.0f / directionCount * i);
			const Vector dir(sinf(rad), -cosf(rad));
			owner->SpawnProjectile(tower.GetPos(), dir, static_cast<float>(tower.GetStat().damage), tower.GetStat().projectileKey);
		}
	}

	void fireHitscan(Tower& tower)
	{
		Bloon* target = tower.GetTarget();
		if (target == nullptr)
			return;

		target->ApplyDamage(static_cast<float>(tower.GetStat().damage));
	}
}

FireBehaviorFn GetFireBehavior(TowerType type)
{
	static const unordered_map<TowerType, FireBehaviorFn> table =
	{
		{ TowerType::DartMonkey,  &fireSingleTarget },
		{ TowerType::TackShooter, &fireEightDirections },
		{ TowerType::SniperMonkey, &fireHitscan},

	};

	// SniperMonkey/BombTower는 아직 발사 로직이 없어서, 붙이기 전까지는 단일 타겟 방식으로 폴백.
	auto it = table.find(type);
	return it != table.end() ? it->second : &fireSingleTarget;
}
