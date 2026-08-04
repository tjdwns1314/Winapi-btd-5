#include "pch.h"
#include "PathFinder.h"

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

    return vector<Vector>();
}
