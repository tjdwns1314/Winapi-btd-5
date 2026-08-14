#include "pch.h"
#include "ObstacleController.h"
#include "Scene.h"
#include "MapSystem.h"
#include "EconomyManager.h"
#include "Obstacle.h"
#include "ObstacleFactory.h"
#include "PoolManager.h"
#include "InputManager.h"

void ObstacleController::TryStartDrag(EconomyManager& economy)
{
	if (economy.GetGold() < GetObstacleStat(ObstacleType::BananaFarmTree).basePrice)
		return; // 골드가 부족하면 드래그를 시작하지 않는다.

	_isDragging = true;
}

void ObstacleController::UpdateDrag(Scene& scene, MapSystem& map, EconomyManager& economy, bool waveActive)
{
	if (_isDragging == false)
		return;

	if (InputManager::GetInstance().GetButtonUp(KeyType::LeftMouse) == false)
		return;

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

	if (findObstacleAt(scene, targetCell, gridSize) != nullptr)
		return; // 이미 장애물이 있는 셀에는 중복 설치 금지

	if (map.TryOccupyCell(targetCell) == false)
		return; // 도착 경로를 완전히 막으면 설치 불가

	const int32 price = GetObstacleStat(ObstacleType::BananaFarmTree).basePrice;
	if (economy.TrySpend(price) == false)
	{
		map.ReleaseCell(targetCell);
		return; // 골드 부족 시 설치 취소
	}

	Obstacle* obstacle = ObstacleFactory::Create(PoolManager::GetInstance().GetObstaclePool(), ObstacleType::BananaFarmTree,
		Vector((targetCell.iX + 0.5f) * gridSize, (targetCell.iY + 0.5f) * gridSize));
	if (obstacle != nullptr)
	{
		scene.AddActor(obstacle);
	}
	else
	{
		economy.Add(price); // 생성 실패 시 차감했던 골드 환불
		map.ReleaseCell(targetCell);
	}
}

void ObstacleController::UpdateSelect(const MapSystem& map, Scene& scene)
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
	_selected = findObstacleAt(scene, clickCell, map.GetGridSize());
}

Obstacle* ObstacleController::findObstacleAt(Scene& scene, const Cell& cell, int32 gridSize) const
{
	for (Actor* actor : scene.GetActors(RenderLayer::Obstacle))
	{
		if (actor->IsPendingKill())
			continue;

		const Cell obstacleCell = Cell::ConvertToCell(actor->GetPos(), gridSize);
		if (obstacleCell.iX == cell.iX && obstacleCell.iY == cell.iY)
			return static_cast<Obstacle*>(actor);
	}
	return nullptr;
}

void ObstacleController::SellSelected(MapSystem& map, EconomyManager& economy)
{
	if (_selected == nullptr)
		return;

	economy.Add(_selected->GetSellPrice());

	const Cell cell = map.WorldToCell(_selected->GetPos());
	map.ReleaseCell(cell);

	_selected->SetPendingKill();
	_selected = nullptr;
}
