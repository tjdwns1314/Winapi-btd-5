#include "pch.h"
#include "Grid.h"
#include "Actor.h"

void Grid::Init(int32 gridCountX, int32 gridCountY, int32 gridSize)
{
	_gridCountX = gridCountX;
	_gridCountY = gridCountY;
	_gridSize = gridSize;

	_grid.resize(static_cast<size_t>(gridCountX) * gridCountY);
}

bool Grid::isValidCell(const Cell& cell) const
{
	return cell.iX >= 0 && cell.iX < _gridCountX
		&& cell.iY >= 0 && cell.iY < _gridCountY;
}

const Grid::GridInfo& Grid::GetGridInfo(const Cell& cell) const
{
	static GridInfo empty;
	if (isValidCell(cell) == false)
		return empty;

	return _grid[cell.iY * _gridCountX + cell.iX];
}

void Grid::UpdateGrid(Actor* actor, const Vector& prevPos)
{
	Cell prevCell = Cell::ConvertToCell(prevPos, _gridSize);
	Cell curCell = Cell::ConvertToCell(actor->GetPos(), _gridSize);

	if (prevCell.iX == curCell.iX && prevCell.iY == curCell.iY)
		return;

	if (isValidCell(prevCell))
	{
		vector<Actor*>& actors = _grid[prevCell.iY * _gridCountX + prevCell.iX].actors;
		actors.erase(remove(actors.begin(), actors.end(), actor), actors.end());
	}

	if (isValidCell(curCell))
	{
		_grid[curCell.iY * _gridCountX + curCell.iX].actors.push_back(actor);
	}
}
