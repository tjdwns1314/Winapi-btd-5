#pragma once
#include "TowerType.h"
#include "ObstacleType.h"

// 타워 1개의 저장 정보. TowerFactory::Create(type, worldPos) 후 grade번 ApplyUpgrade()를 호출해 복원한다.
struct TowerSaveData
{
	TowerType type = TowerType::DartMonkey;
	int32 grade = 1;
	Cell cell;
};

// 장애물 1개의 저장 정보.
struct ObstacleSaveData
{
	ObstacleType type = ObstacleType::BananaFarmTree;
	Cell cell;
};

// 인게임 진행 저장 데이터 전체. 웨이브가 Idle 상태일 때만 저장/로드한다.
// startCell/endCell을 같이 저장해야 로드 시 맵이 랜덤으로 다시 생성되지 않는다.
struct SaveData
{
	static constexpr int32 kVersion = 1;

	int32 gold = 0;
	int32 hp = 0;
	int32 nextRound = 1; // WaveManager::GetNextRoundNumber()
	bool autoPlay = false;
	bool speedEnabled = false;
	Cell startCell;
	Cell endCell;
	vector<TowerSaveData> towers;
	vector<ObstacleSaveData> obstacles;
};
