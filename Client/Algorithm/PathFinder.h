#pragma once
#include "TileMap.h"

// TileMap 위에서 A*로 경로를 계산해 픽셀 좌표 웨이포인트 목록을 반환한다.
class PathFinder
{
public:
	static vector<Vector> FindPath(const TileMap& tileMap, Cell start, Cell end,
		int32 gridCountX, int32 gridCountY, int32 gridSize);
};
