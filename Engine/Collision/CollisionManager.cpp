// Engine/CollisionManager.cpp
#include "pch.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "Actor.h"
#include "Collider.h"

void CollisionManager::RegisterLayer(RenderLayer a, RenderLayer b)
{
	_layerPairs.emplace_back(a, b);
}

void CollisionManager::Update(Scene& scene)
{
	_currPairs.clear();
	for (const pair<RenderLayer, RenderLayer>& layers : _layerPairs)
		checkLayer(scene, layers.first, layers.second);

	for (const pair<Actor*, Actor*>& p : _prevPairs)
	{
		if (_currPairs.find(p) == _currPairs.end())
		{
			p.first->OnExit(p.second);
			p.second->OnExit(p.first);
		}
	}
	_prevPairs = _currPairs;
}

void CollisionManager::checkLayer(Scene& scene, RenderLayer a, RenderLayer b)
{
	// OnEnter 콜백(예: Bloon::spawnNextTier -> Scene::AddActor)이 원본 벡터를
	// 재할당시킬 수 있으므로, 순회 중에는 복사본을 사용한다.
	const vector<Actor*> actorsA = scene.GetActors(a);
	const vector<Actor*> actorsB = scene.GetActors(b);

	for (Actor* actorA : actorsA)
	{
		if (actorA->IsPendingKill() || actorA->GetCollider() == nullptr)
			continue;

		for (Actor* actorB : actorsB)
		{
			// OnEnter 처리 도중 actorA가 pending-kill 상태가 됐다면(예: 발사체 관통 소진)
			// 같은 프레임에 남은 actorB들과는 더 이상 충돌 처리를 하지 않는다.
			if (actorA->IsPendingKill())
				break;

			if (actorB->IsPendingKill() || actorB->GetCollider() == nullptr)
				continue;

			if (actorA->GetCollider()->CheckCollision(actorB->GetCollider()))
			{
				const pair<Actor*, Actor*> key = { actorA, actorB };
				_currPairs.insert(key);

				if (_prevPairs.find(key) == _prevPairs.end())
				{
					actorA->OnEnter(actorB);
					actorB->OnEnter(actorA);
				}
				else
				{
					actorA->OnStay(actorB);
					actorB->OnStay(actorA);
				}
			}
		}
	}
}

void CollisionManager::Reset()
{
	_layerPairs.clear();
	_prevPairs.clear();
	_currPairs.clear();
}

void CollisionManager::RemoveActor(Actor* actor)
{
	std::erase_if(_prevPairs, [actor](const pair<Actor*, Actor*>& p)
	{
		if (p.first != actor && p.second != actor)
			return false;

		Actor* other = (p.first == actor) ? p.second : p.first;
		other->OnExit(actor);
		actor->OnExit(other);
		return true;
	});
}