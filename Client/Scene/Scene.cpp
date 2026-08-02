#include "pch.h"
#include "Scene.h"
#include "Actor.h"

Scene::~Scene()
{
	Cleanup();
}

void Scene::Init(Graphic& graphic)
{
}

void Scene::Cleanup()
{
	for (int32 layer = 0; layer < static_cast<int32>(RenederLayer::Count); ++layer)
	{
		for (Actor* actor : _actors[layer])
			delete actor;

		_actors[layer].clear();
	}

	_postUpdateActions.clear();
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	int32 layer = actor->GetLayer();
	if (layer < 0 || layer >= static_cast<int32>(RenederLayer::Count))
		layer = static_cast<int32>(RenederLayer::Background);

	actor->SetOwner(this);
	_actors[layer].push_back(actor);
}

void Scene::Update(float deltaTime)
{
	for (int32 layer = 0; layer < static_cast<int32>(RenederLayer::Count); ++layer)
	{
		for (Actor* actor : _actors[layer])
		{
			if (actor->IsActive() && actor->IsPendingKill() == false)
				actor->Update(deltaTime);
		}
	}
}

void Scene::Render(Graphic& graphic)
{
	// 배경 → 적 → 총알 → 타워 → 이펙트 순서로 그린다.
	for (int32 layer = 0; layer < static_cast<int32>(RenederLayer::Count); ++layer)
	{
		for (Actor* actor : _actors[layer])
		{
			if (actor->IsActive() && actor->IsPendingKill() == false)
				actor->Render(graphic);
		}
	}
}

void Scene::AddPostUpdateAction(function<void()> action)
{
	_postUpdateActions.push_back(action);
}

void Scene::PostUpdate()
{
	// 1. 예약된 작업 처리 (액터 추가 등)
	//    처리 도중 새 작업이 또 예약될 수 있으므로 비운 뒤 실행한다.
	vector<function<void()>> actions;
	actions.swap(_postUpdateActions);

	for (function<void()>& action : actions)
		action();

	// 2. 죽음 표시된 액터 실제 제거
	for (int32 layer = 0; layer < static_cast<int32>(RenederLayer::Count); ++layer)
	{
		vector<Actor*>& actors = _actors[layer];

		for (int32 i = static_cast<int32>(actors.size()) - 1; i >= 0; --i)
		{
			if (actors[i]->IsPendingKill() == false)
				continue;

			actors[i]->Destroy();
			delete actors[i];
			actors.erase(actors.begin() + i);
		}
	}
}
