#include "pch.h"
#include "PathFinder.h"
#include <queue>
#include <algorithm>
#include <limits>

namespace
{
	struct Node
	{
		Cell cell;
		float f = 0.f;
	};

	struct NodeCompare
	{
		bool operator()(const Node& a, const Node& b) const { return a.f > b.f; }
	};

	float Heuristic(Cell a, Cell b)
	{
		return static_cast<float>(std::abs(a.iX - b.iX) + std::abs(a.iY - b.iY));
	}
}

vector<Vector> PathFinder::FindPath(const TileMap& tileMap, Cell start, Cell end,
	int32 gridCountX, int32 gridCountY, int32 gridSize)
{
	const size_t cellCount = static_cast<size_t>(gridCountX) * gridCountY;
	vector<float> gScore(cellCount, (std::numeric_limits<float>::max)());
	vector<int32> cameFrom(cellCount, -1);
	vector<bool> closed(cellCount, false);

	auto index = [gridCountX](int32 x, int32 y) { return y * gridCountX + x; };

	std::priority_queue<Node, vector<Node>, NodeCompare> open;
	gScore[index(start.iX, start.iY)] = 0.f;
	open.push(Node{ start, Heuristic(start, end) });

	const Cell dirs[4] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
	bool found = false;

	while (open.empty() == false)
	{
		const Node current = open.top();
		open.pop();

		const int32 curIdx = index(current.cell.iX, current.cell.iY);
		if (closed[curIdx])
			continue;
		closed[curIdx] = true;

		if (current.cell.iX == end.iX && current.cell.iY == end.iY)
		{
			found = true;
			break;
		}

		for (const Cell& dir : dirs)
		{
			const int32 nx = current.cell.iX + dir.iX;
			const int32 ny = current.cell.iY + dir.iY;

			if (nx < 0 || nx >= gridCountX || ny < 0 || ny >= gridCountY)
				continue;
			if (tileMap.GetTile(nx, ny) != TileType::Path)
				continue;

			const int32 nIdx = index(nx, ny);
			if (closed[nIdx])
				continue;

			const float tentativeG = gScore[curIdx] + 1.f;
			if (tentativeG < gScore[nIdx])
			{
				gScore[nIdx] = tentativeG;
				cameFrom[nIdx] = curIdx;
				open.push(Node{ Cell{ nx, ny }, tentativeG + Heuristic(Cell{ nx, ny }, end) });
			}
		}
	}

	vector<Vector> path;
	if (found == false)
		return path;

	vector<Cell> cellPath;
	int32 idx = index(end.iX, end.iY);
	while (idx != -1)
	{
		cellPath.push_back(Cell{ idx % gridCountX, idx / gridCountX });
		idx = cameFrom[idx];
	}
	std::reverse(cellPath.begin(), cellPath.end());

	path.reserve(cellPath.size());
	for (const Cell& cell : cellPath)
	{
		path.push_back(Vector((cell.iX + 0.5f) * gridSize, (cell.iY + 0.5f) * gridSize));
	}

	return path;
}
