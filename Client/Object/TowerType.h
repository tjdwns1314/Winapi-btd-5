#pragma once

// 타워 4종 기획: .claude/plan.md 참고. 지금은 DartMonkey/TackShooter만 구현.
enum class TowerType
{
	DartMonkey,
	TackShooter,
	SniperMonkey,
	BombTower,
};

struct TowerGradeStat
{
	int32 cost;
	int32 damage;
	float attackRange;
	float attackSpeed;
	float projectileSpeed;
	int32 attackCount;
	int32 pierceCount = 1;
	float splashRadius = 0.f;
};

struct TowerStat
{
	TowerType type;
	bool rotatesToTarget;
	string projectileKey;
	int32 basePrice;
	int32 refundPrice;
	vector<TowerGradeStat> grades;
};

const TowerStat& GetTowerStat(TowerType type);
TowerType ParseTowerTypeName(const string& name);

struct TowerVisual
{
	bool useBakedImage;
	wstring bakedImageKey;
	string cellName;
};

const TowerVisual& GetTowerVisual(TowerType type);
