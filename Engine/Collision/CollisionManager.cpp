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
	for (Actor* actorA : scene.GetActors(a))
	{
		if (actorA->IsPendingKill() || actorA->GetCollider() == nullptr)
			continue;

		for (Actor* actorB : scene.GetActors(b))
		{
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