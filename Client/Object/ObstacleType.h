#pragma once

// 장애물 1종 기획: 타워처럼 설치 가능한 정적 장애물. 종류가 늘어나면 여기 추가한다.
enum class ObstacleType
{
	BananaFarmChimney,
};

struct ObstacleStat
{
	ObstacleType type;
	int32 basePrice;
	int32 refundPrice;
	string cellName; // InGame.xml 셀 이름
	float renderScale = 1.0f; // 그리드에 배치됐을 때 실제 렌더 크기 배율(1.0 = 원본 크기)
};

const ObstacleStat& GetObstacleStat(ObstacleType type);
