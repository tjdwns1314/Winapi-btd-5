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

// 등급/프레임에 맞는 베이킹 이미지 키를 만들어주는 함수. FireBehaviorFn과 같은 패턴.
// nullptr을 반환하면 그 타워는 애니메이션 없이 TowerVisual::bakedImageKey 한 장만 쓴다.
using TowerFrameKeyFn = void(*)(int32 grade, int32 animFrame, wchar_t* outKey, size_t outKeySize);
TowerFrameKeyFn GetTowerFrameKeyFn(TowerType type);
