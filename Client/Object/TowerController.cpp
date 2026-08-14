#include "pch.h"
#include "TowerController.h"
#include "Scene.h"
#include "MapSystem.h"
#include "EconomyManager.h"
#include "Tower.h"
#include "TowerFactory.h"
#include "PoolManager.h"
#include "InputManager.h"

void TowerController::TryStartDrag(TowerType type, EconomyManager& economy)
{
	if (economy.GetGold() < GetTowerStat(type).basePrice)
		return; // 골드가 부족하면 드래그를 시작하지 않는다.

	_isDragging = true;
	_draggingType = type;
}

void TowerController::UpdateDrag(Scene& scene, MapSystem& map, EconomyManager& economy, bool waveActive)
{
	if (_isDragging == false)
		return;

	if (InputManager::GetInstance().GetButtonUp(KeyType::LeftMouse) == false)
		return;

	const TowerType towerType = _draggingType;
	_isDragging = false;

	const Vector mousePos = InputManager::GetInstance().GetMousePos();
	if (mousePos.x < 0.f || mousePos.x >= GameAreaWidth
		|| mousePos.y < 0.f || mousePos.y >= GameAreaHeight)
		return; // 게임 영역(그리드) 밖에서 손을 떼면 설치하지 않는다.

	const int32 gridSize = map.GetGridSize();
	const Cell targetCell = map.WorldToCell(mousePos);

	if (map.IsStartOrEnd(targetCell))
		return;

	// 웨이브 진행 중에는 풍선이 지나가는 경로 위에 설치하지 못한다.
	if (waveActive && map.IsCellOnPath(targetCell))
		return;

	if (findTowerAt(scene, targetCell, gridSize) != nullptr)
		return; // 이미 타워가 있는 셀에는 중복 설치 금지

	if (map.TryOccupyCell(targetCell) == false)
		return; // 도착 경로를 완전히 막으면 설치 불가

	const int32 price = GetTowerStat(towerType).basePrice;
	if (economy.TrySpend(price) == false)
	{
		map.ReleaseCell(targetCell);
		return; // 골드 부족 시 설치 취소
	}

	Tower* tower = TowerFactory::Create(PoolManager::GetInstance().GetTowerPool(), towerType,
		Vector((targetCell.iX + 0.5f) * gridSize, (targetCell.iY + 0.5f) * gridSize));
	if (tower != nullptr)
	{
		scene.AddActor(tower);
		_selected = tower;
	}
	else
	{
		economy.Add(price); // 생성 실패 시 차감했던 골드 환불
		map.ReleaseCell(targetCell);
	}
}

void TowerController::UpdateSelect(const MapSystem& map, Scene& scene)
{
	if (_isDragging)
		return;

	if (InputManager::GetInstance().GetButtonDown(KeyType::LeftMouse) == false)
		return;

	const Vector mousePos = InputManager::GetInstance().GetMousePos();
	if (mousePos.x < 0.f || mousePos.x >= GameAreaWidth
		|| mousePos.y < 0.f || mousePos.y >= GameAreaHeight)
		return; // 게임 영역 밖(우측 HUD 등) 클릭은 선택에 영향을 주지 않는다.

	const Cell clickCell = map.WorldToCell(mousePos);
	_selected = findTowerAt(scene, clickCell, map.GetGridSize());
}

Tower* TowerController::findTowerAt(Scene& scene, const Cell& cell, int32 gridSize) const
{
	for (Actor* actor : scene.GetActors(RenderLayer::Tower))
	{
		if (actor->IsPendingKill())
			continue;

		const Cell towerCell = Cell::ConvertToCell(actor->GetPos(), gridSize);
		if (towerCell.iX == cell.iX && towerCell.iY == cell.iY)
			return static_cast<Tower*>(actor);
	}
	return nullptr;
}

void TowerController::SellSelected(MapSystem& map, EconomyManager& economy)
{
	if (_selected == nullptr)
		return;

	economy.Add(_selected->GetSellPrice());

	const Cell cell = map.WorldToCell(_selected->GetPos());
	map.ReleaseCell(cell);

	_selected->SetPendingKill();
	_selected = nullptr;
}

void TowerController::UpgradeSelected(EconomyManager& economy)
{
	if (_selected == nullptr || _selected->CanUpgrade() == false)
		return;

	const int32 cost = _selected->GetNextUpgradeCost();
	if (economy.TrySpend(cost) == false)
		return; // 골드 부족

	_selected->ApplyUpgrade();
}
