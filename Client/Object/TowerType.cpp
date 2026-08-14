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
			stat.refundPrice = entry.at("refundPrice").get<int32>();
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
		{ TowerType::TackShooter,  TowerVisual{ true,  L"tack_shooter_baked", "" } },
		{ TowerType::SniperMonkey, TowerVisual{ true,  L"sniper_monkey_baked", "" } },
		{ TowerType::BombTower,    TowerVisual{ true,  L"bomb_tower_baked", "" } },
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

	void dartMonkeyFrameKey(int32 grade, int32 animFrame, wchar_t* outKey, size_t outKeySize)
	{
		swprintf_s(outKey, outKeySize, L"%s_%02d", dartMonkeyAnimKeyPrefix(grade), animFrame + 1);
	}
}

TowerFrameKeyFn GetTowerFrameKeyFn(TowerType type)
{
	static const unordered_map<TowerType, TowerFrameKeyFn> table =
	{
		{ TowerType::DartMonkey, &dartMonkeyFrameKey },
	};
	auto it = table.find(type);
	return it != table.end() ? it->second : nullptr; // 등록 안 된 타워는 애니메이션 없음.
}
