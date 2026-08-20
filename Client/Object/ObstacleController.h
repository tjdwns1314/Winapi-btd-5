#pragma once

class Scene;
class MapSystem;
class EconomyManager;
class Obstacle;

class ObstacleController
{
public:
	void TryStartDrag(Scene& scene, int32 currentRound, EconomyManager& economy);
	void UpdateDrag(Scene& scene, MapSystem& map, EconomyManager& economy, bool waveActive, int32 currentRound);
	void UpdateSelect(const MapSystem& map, Scene& scene);
	void SellSelected(MapSystem& map, EconomyManager& economy);

	bool IsDragging() const { return _isDragging; }
	Obstacle* GetSelected() const { return _selected; }
	void Reset() { _isDragging = false; _selected = nullptr; }

private:
	Obstacle* findObstacleAt(Scene& scene, const Cell& cell, int32 gridSize) const;
	int32 countObstacles(Scene& scene) const;

	bool _isDragging = false;
	Obstacle* _selected = nullptr;
};
