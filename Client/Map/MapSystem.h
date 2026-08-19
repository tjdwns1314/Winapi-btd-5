#pragma once

#include "Grid.h"
#include "TileMap.h"
#include "PathFinder.h"

class Graphic;
class Image;

class MapSystem
{
public:
	void Init();

	const vector<Vector>* GetPathPtr() const { return &_path; }
	Vector GetBloonSpawnPos() const { return _bloonSpawnPos; }
	Vector GetBloonEndPos() const { return _bloonEndPos; }
	int32 GetGridSize() const { return _grid.GetGridSize(); }
	bool HasPath() const { return _path.empty() == false; }

	Cell WorldToCell(const Vector& world) const;
	bool IsCellOnPath(const Cell& cell) const;
	bool IsStartOrEnd(const Cell& cell) const;

	bool TryOccupyCell(const Cell& cell);
	void ReleaseCell(const Cell& cell);

	void SetTileImages(Image* tile1, Image* tile2) { _tile1Img = tile1; _tile2Img = tile2; }
	void RenderTiles(Graphic& graphic) const;
	void RenderGrid(Graphic& graphic, const D2D1::ColorF& color = D2D1::ColorF(D2D1::ColorF::Gray, 0.5f)) const;
	void RenderPathDebug(Graphic& graphic) const;

private:
	void recomputePath();

	Grid _grid;
	TileMap _tileMap;
	vector<Vector> _path;
	Vector _bloonSpawnPos;
	Vector _bloonEndPos;

	Image* _tile1Img = nullptr;
	Image* _tile2Img = nullptr;
};
