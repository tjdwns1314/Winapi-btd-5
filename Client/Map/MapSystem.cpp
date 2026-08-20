#include "pch.h"
#include "MapSystem.h"
#include "Image.h"

void MapSystem::Init(const Cell* forcedStart, const Cell* forcedEnd)
{
	_grid.Init(GRID_COUNT_X, GRID_COUNT_Y, BLOCK_SIZE);
	_tileMap.Init(GRID_COUNT_X, GRID_COUNT_Y);

	if (forcedStart != nullptr && forcedEnd != nullptr)
		_tileMap.SetStartEndPoint(*forcedStart, *forcedEnd);
	else
		_tileMap.GenerateRandomStartEndPoint();

	recomputePath();
	RecomputeRiskPath({}); // 아직 타워가 없으니 위험도 0인 최단 경로로 시작

	const Cell startCell = _tileMap.GetStartPoint();
	const int32 gridSize = _grid.GetGridSize();
	_bloonSpawnPos = Vector(
		(startCell.iX + 0.5f) * gridSize,
		(startCell.iY + 0.5f) * gridSize);

	const Cell endCell = _tileMap.GetEndPoint();
	_bloonEndPos = Vector(
		(endCell.iX + 0.5f) * gridSize,
		(endCell.iY + 0.5f) * gridSize);
}

void MapSystem::recomputePath()
{
	_path = PathFinder::FindPath(_tileMap, _tileMap.GetStartPoint(), _tileMap.GetEndPoint(),
		GRID_COUNT_X, GRID_COUNT_Y, _grid.GetGridSize());
}

void MapSystem::RecomputeRiskPath(const vector<PathFinder::RiskSource>& towers)
{
	_riskPath = PathFinder::FindRiskPath(_tileMap.GetStartPoint(), _tileMap.GetEndPoint(),
		GRID_COUNT_X, GRID_COUNT_Y, _grid.GetGridSize(), towers);
}

Cell MapSystem::WorldToCell(const Vector& world) const
{
	return Cell::ConvertToCell(world, _grid.GetGridSize());
}

bool MapSystem::IsCellOnPath(const Cell& cell) const
{
	const int32 gridSize = _grid.GetGridSize();
	for (const Vector& point : _path)
	{
		const Cell pathCell = Cell::ConvertToCell(point, gridSize);
		if (pathCell.iX == cell.iX && pathCell.iY == cell.iY)
			return true;
	}
	return false;
}

bool MapSystem::IsStartOrEnd(const Cell& cell) const
{
	const Cell startCell = _tileMap.GetStartPoint();
	const Cell endCell = _tileMap.GetEndPoint();
	return (cell.iX == startCell.iX && cell.iY == startCell.iY) || (cell.iX == endCell.iX && cell.iY == endCell.iY);
}

bool MapSystem::TryOccupyCell(const Cell& cell)
{
	const bool wasOnPath = IsCellOnPath(cell);

	_tileMap.SetTile(cell.iX, cell.iY, TileType::Obstacle);

	vector<Vector> newPath = PathFinder::FindPath(_tileMap, _tileMap.GetStartPoint(),
		_tileMap.GetEndPoint(), GRID_COUNT_X, GRID_COUNT_Y, _grid.GetGridSize());
	if (newPath.empty())
	{
		_tileMap.SetTile(cell.iX, cell.iY, TileType::Path);
		return false;
	}

	// 원래 경로 위의 셀을 막았거나(모양이 바뀜) 코스트(길이)가 달라졌으면 경로를 다시 그림
	if (wasOnPath || newPath.size() != _path.size())
	{
		_path = std::move(newPath);
	}

	return true;
}

void MapSystem::ReleaseCell(const Cell& cell)
{
	_tileMap.SetTile(cell.iX, cell.iY, TileType::Path);

	vector<Vector> newPath = PathFinder::FindPath(_tileMap, _tileMap.GetStartPoint(),
		_tileMap.GetEndPoint(), GRID_COUNT_X, GRID_COUNT_Y, _grid.GetGridSize());
	if (newPath.empty() == false && newPath.size() != _path.size())
		_path = std::move(newPath);
}

void MapSystem::RenderTiles(Graphic& graphic) const
{
	if (_tile1Img == nullptr || _tile2Img == nullptr)
		return;

	const D2D1_SIZE_F size1 = _tile1Img->GetSize();
	const float scale1 = static_cast<float>(BLOCK_SIZE) / size1.width;

	const D2D1_SIZE_F size2 = _tile2Img->GetSize();
	const float scale2 = static_cast<float>(BLOCK_SIZE) / size2.width;

	for (int32 y = 0; y < GRID_COUNT_Y; ++y)
	{
		for (int32 x = 0; x < GRID_COUNT_X; ++x)
		{
			const TileType tile = _tileMap.GetTile(x, y);
			if (tile != TileType::Path && tile != TileType::Obstacle)
				continue;

			const float cx = (x + 0.5f) * BLOCK_SIZE;
			const float cy = (y + 0.5f) * BLOCK_SIZE;
			if (tile == TileType::Path)
				_tile1Img->Draw(graphic, cx, cy, scale1);
			else
				_tile2Img->Draw(graphic, cx, cy, scale2);
		}
	}
}

void MapSystem::RenderGrid(Graphic& graphic, const D2D1::ColorF& color) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(color);
	if (renderTarget == nullptr || brush == nullptr)
		return;

	const int32 gridSize = _grid.GetGridSize();
	const float width = static_cast<float>(GRID_COUNT_X * gridSize);
	const float height = static_cast<float>(GRID_COUNT_Y * gridSize);

	for (int32 x = 0; x <= GRID_COUNT_X; ++x)
	{
		const float px = static_cast<float>(x * gridSize);
		renderTarget->DrawLine(D2D1::Point2F(px, 0.f), D2D1::Point2F(px, height), brush);
	}

	for (int32 y = 0; y <= GRID_COUNT_Y; ++y)
	{
		const float py = static_cast<float>(y * gridSize);
		renderTarget->DrawLine(D2D1::Point2F(0.f, py), D2D1::Point2F(width, py), brush);
	}
}

void MapSystem::RenderPathDebug(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Blue));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	if (_path.size() <= 2)
		return;

	const float radius = static_cast<float>(_grid.GetGridSize()) * 0.15f;

	for (size_t i = 1; i + 1 < _path.size(); ++i)
	{
		const Vector& point = _path[i];
		renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(point.x, point.y), radius, radius), brush);
	}
}

void MapSystem::RenderRiskPathDebug(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Red));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	if (_riskPath.size() <= 2)
		return;

	const float radius = static_cast<float>(_grid.GetGridSize()) * 0.15f;

	for (size_t i = 1; i + 1 < _riskPath.size(); ++i)
	{
		const Vector& point = _riskPath[i];
		renderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(point.x, point.y), radius, radius), brush);
	}
}

