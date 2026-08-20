#pragma once
#include "TileMap.h"

// TileMap 위에서 A*로 경로를 계산해 픽셀 좌표 웨이포인트 목록을 반환한다.
class PathFinder
{
public:
	static vector<Vector> FindPath(const TileMap& tileMap, Cell start, Cell end,
		int32 gridCountX, int32 gridCountY, int32 gridSize);

	struct RiskSource
	{
		Vector pos;
		float range = 0.f;
	};

	// 타일 종류(Path/Buildable/Obstacle)와 무관하게 그리드 전체에서 A*로 경로를 계산한다.
	// RiskSource(타워 사거리)가 많이 겹치는 칸일수록 이동 비용이 커진다. 특수 풍선 전용 경로.
	static vector<Vector> FindRiskPath(Cell start, Cell end, int32 gridCountX, int32 gridCountY, int32 gridSize,
		const vector<RiskSource>& riskSources);
};
