#include "pch.h"
#include "ObstacleType.h"

const ObstacleStat& GetObstacleStat(ObstacleType type)
{
	static const unordered_map<ObstacleType, ObstacleStat> table =
	{
		{ ObstacleType::BananaFarmTree, ObstacleStat{ ObstacleType::BananaFarmTree, 20, 10, "banana_farm_tree" } },
	};
	return table.at(type);
}
