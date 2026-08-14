#pragma once
#include "TowerType.h"

class Scene;
class MapSystem;
class EconomyManager;
class Tower;

class TowerController
{
public:
	void TryStartDrag(TowerType type, EconomyManager& economy);
	void UpdateDrag(Scene& scene, MapSystem& map, EconomyManager& economy, bool waveActive);
	void UpdateSelect(const MapSystem& map, Scene& scene);
	void SellSelected(MapSystem& map, EconomyManager& economy);
	void UpgradeSelected(EconomyManager& economy);

	bool IsDragging() const { return _isDragging; }
	TowerType DraggingType() const { return _draggingType; }
	Tower* GetSelected() const { return _selected; }
	void Reset() { _isDragging = false; _selected = nullptr; }

private:
	Tower* findTowerAt(Scene& scene, const Cell& cell, int32 gridSize) const;

	bool _isDragging = false;
	TowerType _draggingType = TowerType::DartMonkey;
	Tower* _selected = nullptr;
};
