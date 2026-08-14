#include "pch.h"
#include "TowerFireBehavior.h"
#include "Tower.h"
#include "GameScene.h"

namespace
{
	bool prepareDirectedFire(Tower& tower, GameScene*& owner, Vector& dir)
	{
		Bloon* target = tower.GetTarget();
		if (target == nullptr)
			return false;

		owner = tower.GetGameScene();
		if (owner == nullptr)
			return false;

		dir = target->GetPos() - tower.GetPos();
		if (dir.Length() < SMALL_NUMBER)
			return false;

		dir.Normalize();
		return true;
	}

	// 다트원숭이: 타겟 방향으로 1발, attackCount가 3 이상이면 좌우 10도씩 추가로 2발 더 발사.
	void fireDartMonkey(Tower& tower)
	{
		GameScene* owner = nullptr;
		Vector dir;
		if (prepareDirectedFire(tower, owner, dir) == false)
			return;

		const auto spawnDart = [&](const Vector& d)
		{
			owner->SpawnProjectile(tower.GetPos(), d, static_cast<float>(tower.GetStat().damage),
				tower.GetTowerData().projectileKey, tower.GetStat().projectileSpeed,
				0.f, tower.GetStat().pierceCount);
		};

		spawnDart(dir);

		if (tower.GetStat().attackCount >= 3)
		{
			spawnDart(dir.Rotate(DegreeToRadian(10.f)));
			spawnDart(dir.Rotate(DegreeToRadian(-10.f)));
		}
	}

	// 압정슈터: 사거리 안에 적이 있을 때만 attackCount방향으로 동시에 발사(기본 8, 5등급 16). 방향 자체는 타겟을 따라가지 않는다.
	void fireTackShooter(Tower& tower)
	{
		if (tower.GetTarget() == nullptr)
			return;

		GameScene* owner = tower.GetGameScene();
		if (owner == nullptr)
			return;

		const int32 directionCount = tower.GetStat().attackCount;
		for (int32 i = 0; i < directionCount; ++i)
		{
			const float rad = DegreeToRadian(360.0f / directionCount * i);
			const Vector dir(sinf(rad), -cosf(rad));
			owner->SpawnProjectile(tower.GetPos(), dir, static_cast<float>(tower.GetStat().damage),
				tower.GetTowerData().projectileKey, tower.GetStat().projectileSpeed,
				0.f, tower.GetStat().pierceCount);
		}
	}

	// 폭탄타워: 타겟 방향으로 발사, 명중 지점 splashRadius 안의 풍선에게 전부 데미지.
	void fireBombTower(Tower& tower)
	{
		GameScene* owner = nullptr;
		Vector dir;
		if (prepareDirectedFire(tower, owner, dir) == false)
			return;

		owner->SpawnProjectile(tower.GetPos(), dir, static_cast<float>(tower.GetStat().damage),
			tower.GetTowerData().projectileKey, tower.GetStat().projectileSpeed,
			tower.GetStat().splashRadius, tower.GetStat().pierceCount);
	}

	// 저격원숭이: 히트스캔(투사체 없이 즉시 타겟에게 데미지).
	void fireSniperMonkey(Tower& tower)
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
		{ TowerType::DartMonkey,   &fireDartMonkey },
		{ TowerType::TackShooter,  &fireTackShooter },
		{ TowerType::SniperMonkey, &fireSniperMonkey },
		{ TowerType::BombTower,    &fireBombTower },
	};

	// 타워 4종은 항상 여기에 다 매핑되어 있지만, 방어적으로 다트원숭이로 폴백.
	auto it = table.find(type);
	return it != table.end() ? it->second : &fireDartMonkey;
}
