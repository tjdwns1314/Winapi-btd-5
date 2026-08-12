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
			stat.type =
				ParseTowerTypeName(entry.at("type").get<string>());
			stat.damage = entry.at("damage").get<int32>();
			stat.attackRange = entry.at("attackRange").get<float>();
			stat.attackSpeed = entry.at("attackSpeed").get<float>();
			stat.rotatesToTarget = entry.at("rotatesToTarget").get<bool>();
			stat.attackCount = entry.at("attackCount").get<int32>();
			stat.projectileKey = entry.at("projectileKey").get<string>();
			stat.basePrice = entry.at("basePrice").get<int32>();
			stat.refundPrice = entry.at("refundPrice").get<int32>();

			for (const auto& cost : entry.at("upgradeCosts"))
				stat.upgradeCosts.push_back(cost.get <int32>());

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
	return stats[static_cast<size_t>(type)];
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
	return table.at(name);
}

const TowerVisual& GetTowerVisual(TowerType type)
{
	// TODO: 스탯(공속/데미지 등)까지 필요해지면 BloonType처럼 JSON(Resource\Data\TowerType.json)으로 옮긴다.
	static const unordered_map<TowerType, TowerVisual> table =
	{
		{ TowerType::DartMonkey,  TowerVisual{ true,  L"dart_monkey_baked", "" } },
		{ TowerType::TackShooter, TowerVisual{ true,  L"tack_shooter_baked", "" } },
		{ TowerType::SniperMonkey, TowerVisual{ true, L"sniper_monkey_baked", "" } },
		{ TowerType::BombTower, TowerVisual{ true,  L"bomb_tower_baked", "" } },
	};
	return table.at(type);
}
