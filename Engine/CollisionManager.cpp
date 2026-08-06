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
	for (const pair<RenderLayer, RenderLayer>& layers : _layerPairs)
		checkLayer(scene, layers.first, layers.second);
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
				actorA->OnEnter(actorB);
				actorB->OnEnter(actorA);
			}
		}
	}
}