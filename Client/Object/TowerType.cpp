#include "pch.h"
#include "TowerType.h"
#include "External/json.hpp"
#include <fstream>

namespace
{
	vector<TowerStat> loadTowerStats()
	{
		vector<TowerStat> stats;
		std::ifstream file("Resource\\Data\\TowerType.json");
		if (!file.is_open())
		{
			MessageBox(nullptr, L"Resource\\Data\\TowerType.json", L"TowerType 데이터 로드 실패", MB_OK);
			return stats;
		}
		nlohmann::json root;
		file >> root;

		for (const auto& entry : root.at("towers"))
		{
			TowerStat stat;
			stat.type = ParseTowerTypeName(entry.at("type").get<string>());
			stat.rotatesToTarget = entry.at("rotatesToTarget").get<bool>();
			stat.projectileKey = entry.at("projectileKey").get<string>();
			stat.basePrice = entry.at("basePrice").get<int32>();
			for (const auto& g : entry.at("grades"))
			{
				TowerGradeStat grade;
				grade.cost = g.at("cost").get<int32>();
				grade.damage = g.at("damage").get<int32>();
				grade.attackRange = g.at("attackRange").get<float>();
				grade.attackSpeed = g.at("attackSpeed").get<float>();
				grade.projectileSpeed = g.at("projectileSpeed").get<float>();
				grade.attackCount = g.at("attackCount").get<int32>();
				grade.pierceCount = g.value("pierceCount", 1);
				grade.splashRadius = g.value("splashRadius", 0.f);
				grade.projectileKey = g.value("projectileKey", string());
				stat.grades.push_back(grade);
			}

			stats.push_back(std::move(stat));
		}
		std::sort(stats.begin(), stats.end(), [](const TowerStat& a, const TowerStat& b)
		{
			return static_cast<int32>(a.type) < static_cast<int32>(b.type);
		});
		return stats;
	}
}

const TowerStat& GetTowerStat(TowerType type)
{
	static const vector<TowerStat> stats = loadTowerStats();
	const size_t index = static_cast<size_t>(type);
	if (index >= stats.size())
	{
		static const TowerStat fallback{};
		return fallback;
	}
	return stats[index];
}

TowerType ParseTowerTypeName(const string& name)
{
	static const unordered_map<string, TowerType> table =
	{
		{"DartMonkey", TowerType::DartMonkey},
		{"TackShooter", TowerType::TackShooter},
		{"SniperMonkey", TowerType::SniperMonkey},
		{"BombTower", TowerType::BombTower},
	};
	auto it = table.find(name);
	return it != table.end() ? it->second : TowerType::DartMonkey;
}

const TowerVisual& GetTowerVisual(TowerType type)
{
	// TODO: 스탯(공속/데미지 등)까지 필요해지면 BloonType처럼 JSON(Resource\Data\TowerType.json)으로 옮긴다.
	static const unordered_map<TowerType, TowerVisual> table =
	{
		{ TowerType::DartMonkey,   TowerVisual{ true,  L"dart_monkey_base_baked_01", ""} },
		{ TowerType::TackShooter,  TowerVisual{ true,  L"tack_shooter_grade1_baked_01", "" } },
		{ TowerType::SniperMonkey, TowerVisual{ true,  L"sniper_grade1_baked_idle", "" } },
		{ TowerType::BombTower,    TowerVisual{ true,  L"bomb_tower_grade1_baked_01", "" } },
	};
	return table.at(type);
}

namespace
{
	// 1등급=base, 2=red, 3=blue, 4=green, 5=triple.
	const wchar_t* dartMonkeyAnimKeyPrefix(int32 grade)
	{
		static const wchar_t* prefixes[] =
		{
			L"dart_monkey_base_baked",
			L"dart_monkey_red_baked",
			L"dart_monkey_blue_baked",
			L"dart_monkey_green_baked",
			L"dart_monkey_triple_baked",
		};
		const int32 index = std::clamp(grade - 1, 0, static_cast<int32>(std::size(prefixes)) - 1);
		return prefixes[index];
	}
	constexpr int32 kDartMonkeyThrowFrameCount = 3;

	int32 dartMonkeyFrameKey(int32 grade, int32 animFrame, bool isThrowing, wchar_t* outKey, size_t outKeySize)
	{
		swprintf_s(outKey, outKeySize, L"%s_%02d", dartMonkeyAnimKeyPrefix(grade), animFrame + 1);
		return kDartMonkeyThrowFrameCount;
	}

	constexpr int32 kTackShooterThrowFrameCount = 2;

	// 1등급=firing+tack_logo 좌우대칭, 2등급=firing 유지+로고만 even_faster로 교체,
	// 3등급=2등급과 소스 셀이 완전히 동일 → 같은 baked 키 재사용(렌더 크기 차이는 GetTowerGradeScale로 처리),
	// 4등급=faster_firing 셀, 5등급=sprayer 셀.
	const wchar_t* tackShooterAnimKeyPrefix(int32 grade)
	{
		static const wchar_t* prefixes[] =
		{
			L"tack_shooter_grade1_baked",
			L"tack_shooter_grade2_baked",
			L"tack_shooter_grade2_baked", // 3등급: 2등급과 동일 이미지
			L"tack_shooter_grade4_baked",
			L"tack_shooter_grade5_baked",
		};
		const int32 index = std::clamp(grade - 1, 0, static_cast<int32>(std::size(prefixes)) - 1);
		return prefixes[index];
	}

	int32 tackShooterFrameKey(int32 grade, int32 animFrame, bool isThrowing, wchar_t* outKey, size_t outKeySize)
	{
		swprintf_s(outKey, outKeySize, L"%s_%02d", tackShooterAnimKeyPrefix(grade), animFrame + 1);
		return kTackShooterThrowFrameCount;
	}

	// 저격원숭이: 정지 시 bolt_action(볼트액션) 정적 포즈, 발사 시 arm_01~05 애니메이션.
	// 발사 프레임 1~4에는 튕겨나오는 탄피(casing_01~04)가 같이 붙고, 마지막 프레임(05)엔 탄피 없음.
	// 등급별로 액세서리(모자/선글라스/고글/불구화 로고)만 바뀌고 나머지 파츠는 동일 → 등급마다 idle 1장 + 발사 5장 = 6장.
	constexpr int32 kSniperMonkeyThrowFrameCount = 5;

	const wchar_t* sniperMonkeyAnimKeyPrefix(int32 grade)
	{
		static const wchar_t* prefixes[] =
		{
			L"sniper_grade1_baked",
			L"sniper_grade2_baked",
			L"sniper_grade3_baked",
			L"sniper_grade4_baked",
			L"sniper_grade5_baked",
		};
		const int32 index = std::clamp(grade - 1, 0, static_cast<int32>(std::size(prefixes)) - 1);
		return prefixes[index];
	}

	int32 sniperMonkeyFrameKey(int32 grade, int32 animFrame, bool isThrowing, wchar_t* outKey, size_t outKeySize)
	{
		if (isThrowing)
			swprintf_s(outKey, outKeySize, L"%s_%02d", sniperMonkeyAnimKeyPrefix(grade), animFrame + 1);
		else
			swprintf_s(outKey, outKeySize, L"%s_idle", sniperMonkeyAnimKeyPrefix(grade));
		return kSniperMonkeyThrowFrameCount;
	}

	// TODO(미검증): 압정 다트 3등급부터 커지는 배율. 실제 렌더링 확인 후 조정 필요.
	constexpr float kTackShooterBiggerScale = 1.3f;
	constexpr float kTowerBaseScale = 0.7f;

	// 폭탄타워 1~4등급: 4프레임 공용 프리픽스 테이블. 5등급(미사일)은 idle/발사 시퀀스가 완전히 달라 별도 처리한다.
	const wchar_t* bombTowerAnimKeyPrefix(int32 grade)
	{
		static const wchar_t* prefixes[] =
		{
			L"bomb_tower_grade1_baked",
			L"bomb_tower_grade2_baked",
			L"bomb_tower_grade3_baked",
			L"bomb_tower_grade4_baked",
		};
		const int32 index = std::clamp(grade - 1, 0, static_cast<int32>(std::size(prefixes)) - 1);
		return prefixes[index];
	}
	constexpr int32 kBombTowerBaseFrameCount = 4;

	// 5등급: idle엔 완전체 미사일을 들고 있다가, 발사가 시작되면 사일로 문이 01→06으로 열리며(문02~04에서 새
	// 미사일이 01→03으로 자라나고 문05부터 완전체로 바뀐 채 유지) 06→01로 다시 닫힌다. 문이 완전히 닫힌
	// 시점(=애니메이션 마지막 프레임이 끝나는 시점, GetTowerFiresAtAnimStart=false 기본 규칙)에 발사된다.
	constexpr int32 kBombTowerGrade5FrameCount = 11; // 열림 6(01~06) + 닫힘 5(05~01)

	int32 bombTowerFrameKey(int32 grade, int32 animFrame, bool isThrowing, wchar_t* outKey, size_t outKeySize)
	{
		if (grade >= 5)
		{
			if (!isThrowing)
				swprintf_s(outKey, outKeySize, L"bomb_tower_grade5_baked_idle");
			else
				swprintf_s(outKey, outKeySize, L"bomb_tower_grade5_baked_%02d", animFrame + 1);
			return kBombTowerGrade5FrameCount;
		}
		swprintf_s(outKey, outKeySize, L"%s_%02d", bombTowerAnimKeyPrefix(grade), animFrame + 1);
		return kBombTowerBaseFrameCount;
	}
}

TowerFrameKeyFn GetTowerFrameKeyFn(TowerType type)
{
	static const unordered_map<TowerType, TowerFrameKeyFn> table =
	{
		{ TowerType::DartMonkey, &dartMonkeyFrameKey },
		{ TowerType::TackShooter, &tackShooterFrameKey },
		{ TowerType::SniperMonkey, &sniperMonkeyFrameKey },
		{ TowerType::BombTower, &bombTowerFrameKey },
	};
	auto it = table.find(type);
	return it != table.end() ? it->second : nullptr;
}

float GetTowerGradeScale(TowerType type, int32 grade)
{
	if (type == TowerType::TackShooter && grade >= 3)
		return kTackShooterBiggerScale * kTowerBaseScale;
	return kTowerBaseScale;
}

bool GetTowerFiresAtAnimStart(TowerType type, int32 grade)
{
	if (type == TowerType::SniperMonkey)
		return true;
	if (type == TowerType::BombTower && grade >= 5)
		return true; // 사일로 문 애니메이션은 발사 이후의 "재장전" 연출일 뿐, 발사 자체는 쿨타임이 차자마자 즉시 일어난다.
	return false;
}
