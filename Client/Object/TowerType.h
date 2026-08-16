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

// outKey에 이미지 키를 채우고, 그 타워의 던지기 애니메이션 총 프레임 수를 반환한다.
// GetTowerFrameKeyFn이 nullptr을 반환하면 그 타워는 애니메이션 없이 TowerVisual::bakedImageKey 한 장만 쓴다.
using TowerFrameKeyFn = int32(*)(int32 grade, int32 animFrame, wchar_t* outKey, size_t outKeySize);
TowerFrameKeyFn GetTowerFrameKeyFn(TowerType type);

// 등급별 렌더 스케일 배수(Actor::SetScale에 사용). 대부분 1.0, 필요한 타워/등급만 재정의.
float GetTowerGradeScale(TowerType type, int32 grade);
