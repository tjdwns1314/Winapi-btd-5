#pragma once

#include "Grid.h"
#include "TileMap.h"
#include "PathFinder.h"

class Graphic;
class Image;

class MapSystem
{
public:
	// forcedStart/forcedEnd가 둘 다 있으면 그 값을 쓰고, 없으면 기존처럼 랜덤 생성한다(불러오기용).
	void Init(const Cell* forcedStart = nullptr, const Cell* forcedEnd = nullptr);

	const vector<Vector>* GetPathPtr() const { return &_path; }
	const vector<Vector>* GetRiskPathPtr() const { return &_riskPath; }
	Vector GetBloonSpawnPos() const { return _bloonSpawnPos; }
	Vector GetBloonEndPos() const { return _bloonEndPos; }
	Cell GetStartCell() const { return _tileMap.GetStartPoint(); }
	Cell GetEndCell() const { return _tileMap.GetEndPoint(); }
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
	void RenderRiskPathDebug(Graphic& graphic) const;

	// 타워 목록(위치+사거리)을 받아 위험도 가중 A*로 특수 풍선 전용 경로를 다시 계산한다.
	// 특수 웨이브가 시작될 때만 호출하면 된다.
	void RecomputeRiskPath(const vector<PathFinder::RiskSource>& towers);

private:
	void recomputePath();

	Grid _grid;
	TileMap _tileMap;
	vector<Vector> _path;
	vector<Vector> _riskPath; // 특수 풍선 전용. _path와 별개로 관리.
	Vector _bloonSpawnPos;
	Vector _bloonEndPos;

	Image* _tile1Img = nullptr;
	Image* _tile2Img = nullptr;
};
