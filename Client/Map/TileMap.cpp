#include "pch.h"
#include "TileMap.h"
#include <random>

void TileMap::Init(int32 gridCountX, int32 gridCountY, TileType fillType)
{
	_gridCountX = gridCountX;
	_gridCountY = gridCountY;
	_tiles.assign(static_cast<size_t>(gridCountX) * gridCountY, fillType);
}

TileType TileMap::GetTile(int32 x, int32 y) const
{
	if (isValidCell(x, y) == false)
		return TileType::Obstacle;
	return _tiles[y * _gridCountX + x];
}

void TileMap::SetTile(int32 x, int32 y, TileType type)
{
	if (isValidCell(x, y) == false)
		return;
	_tiles[y * _gridCountX + x] = type;
}

void TileMap::GenerateRandomStartEndPoint()
{
	static std::mt19937 rng{ std::random_device{}() };

	// 0 = 좌우(Left<->Right), 1 = 상하(Top<->Bottom)
	std::uniform_int_distribution<int32> axisDist(0, 1);
	std::uniform_int_distribution<int32> sideDist(0, 1);

	if (axisDist(rng) == 0)
	{
		std::uniform_int_distribution<int32> yDist(0, _gridCountY - 1);
		const bool startLeft = sideDist(rng) == 0;

		_startCell = Cell{ startLeft ? 0 : _gridCountX - 1, yDist(rng) };
		_endCell = Cell{ startLeft ? _gridCountX - 1 : 0, yDist(rng) };
	}
	else
	{
		std::uniform_int_distribution<int32> xDist(0, _gridCountX - 1);
		const bool startTop = sideDist(rng) == 0;

		_startCell = Cell{ xDist(rng), startTop ? 0 : _gridCountY - 1 };
		_endCell = Cell{ xDist(rng), startTop ? _gridCountY - 1 : 0 };
	}
}

bool TileMap::isValidCell(int32 x, int32 y) const
{
	return x >= 0 && x < _gridCountX && y >= 0 && y < _gridCountY;
}


