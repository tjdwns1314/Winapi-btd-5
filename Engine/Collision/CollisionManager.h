#pragma once
#include "Singleton.h"

class Scene;
class Actor;

class CollisionManager : public Singleton<CollisionManager>
{
	friend Singleton<CollisionManager>;

public:
	void RegisterLayer(RenderLayer a, RenderLayer b);
	void Update(Scene& scene);

	// Scene::PostUpdate가 액터를 delete/Pool 반환하기 직전에 호출한다.
	// 다음 프레임까지 기다려 Exit를 판정하면 댕글링/풀 재사용 문제가 생기므로
	// 파괴 직전 이 시점에 즉시 OnExit를 통지하고 추적 목록에서 제거한다.
	void RemoveActor(Actor* actor);
private:
	CollisionManager() = default;
	~CollisionManager() = default;

	void checkLayer(Scene& scene, RenderLayer a, RenderLayer b);

	vector<pair<RenderLayer, RenderLayer>> _layerPairs;

	// 프레임 간 충돌 쌍 생존 상태를 비교해 Enter/Stay/Exit를 판정한다.
	set<pair<Actor*, Actor*>> _prevPairs;
	set<pair<Actor*, Actor*>> _currPairs;
};

