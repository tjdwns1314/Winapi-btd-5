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
	string projectileKey; // 비어있으면 TowerStat::projectileKey를 그대로 쓴다. 등급마다 다른 투사체가 필요할 때만 채운다(예: 폭탄타워 5등급 미사일).
	string upgradeIconKey; // upgrade_icons.xml 셀 이름. 비어있으면(base grade) 표시할 아이콘 없음.
};

struct TowerStat
{
	TowerType type;
	bool rotatesToTarget;
	string projectileKey;
	int32 basePrice;
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

// 선택 패널 등 UI에 표시할 한글 이름.
const wchar_t* GetTowerDisplayName(TowerType type);

// outKey에 이미지 키를 채우고, 그 타워의 던지기 애니메이션 총 프레임 수를 반환한다.
// GetTowerFrameKeyFn이 nullptr을 반환하면 그 타워는 애니메이션 없이 TowerVisual::bakedImageKey 한 장만 쓴다.
using TowerFrameKeyFn = int32(*)(int32 grade, int32 animFrame, bool isThrowing, wchar_t* outKey, size_t outKeySize);
TowerFrameKeyFn GetTowerFrameKeyFn(TowerType type);

// 등급별 렌더 스케일 배수(Actor::SetScale에 사용). 대부분 1.0, 필요한 타워/등급만 재정의.
float GetTowerGradeScale(TowerType type, int32 grade);

// true면 던지기/발사 애니메이션의 첫 프레임 진입 시점에 곧바로 발사하고, 이후 프레임은 순수 연출(예: 스나이퍼의 재장전 모션)이다.
// false(기본)면 기존처럼 애니메이션이 다 끝난 시점에 발사한다(다트/압정처럼 던지는 동작 끝에 투사체가 나가는 경우).
bool GetTowerFiresAtAnimStart(TowerType type, int32 grade);
