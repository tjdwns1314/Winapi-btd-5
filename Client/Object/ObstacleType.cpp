#include "pch.h"
#include "ObstacleType.h"

const ObstacleStat& GetObstacleStat(ObstacleType type)
{
	static const unordered_map<ObstacleType, ObstacleStat> table =
	{
		{ ObstacleType::BananaFarmChimney, ObstacleStat{ ObstacleType::BananaFarmChimney, 20, 10, "banana_farm_chimney_02", 0.7f } },
	};
	return table.at(type);
}
