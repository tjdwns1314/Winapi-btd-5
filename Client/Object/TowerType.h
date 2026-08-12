#pragma once

// 타워 4종 기획: .claude/plan.md 참고. 지금은 DartMonkey/TackShooter만 구현.
enum class TowerType
{
	DartMonkey,
	TackShooter,
	SniperMonkey,
	BombTower,
};

struct TowerStat
{
	TowerType type;
	int32 damage;
	float attackRange;
	float attackSpeed;
	float projectileSpeed;
	bool rotatesToTarget;
	int32 attackCount;
	string projectileKey;
	int32 basePrice;
	int32 refundPrice;
	vector<int32> upgradeCosts;
};

const TowerStat& GetTowerStat(TowerType type);
TowerType ParseTowerTypeName(const string& name);

// 타워 종류별로 어떤 이미지를 그릴지 정의한다.
// useBakedImage == true면 ResourceManager::BakeImage로 미리 구운 합성 텍스처(bakedImageKey)를 통째로 그리고,
// false면 atlas에서 cellName 셀 하나를 조회해서 그린다.
struct TowerVisual
{
	bool useBakedImage;
	wstring bakedImageKey;
	string cellName;
};

const TowerVisual& GetTowerVisual(TowerType type);
