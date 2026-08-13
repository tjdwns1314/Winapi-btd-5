#pragma once

// 장애물 1종 기획: 타워처럼 설치 가능한 정적 장애물. 종류가 늘어나면 여기 추가한다.
enum class ObstacleType
{
	BananaFarmTree,
};

struct ObstacleStat
{
	ObstacleType type;
	int32 basePrice;
	int32 refundPrice;
	string cellName; // InGame.xml 셀 이름
};

const ObstacleStat& GetObstacleStat(ObstacleType type);
