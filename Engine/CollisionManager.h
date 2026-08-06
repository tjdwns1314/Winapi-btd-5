#pragma once
#include "Singleton.h"

class Scene;

class CollisionManager : public Singleton<CollisionManager>
{
	friend Singleton<CollisionManager>;

public:
	void RegisterLayer(RenderLayer a, RenderLayer b);
	void Update(Scene& scene);
private:
	CollisionManager() = default;
	~CollisionManager() = default;

	void checkLayer(Scene& scene, RenderLayer a, RenderLayer b);
	vector<pair<RenderLayer, RenderLayer>> _layerPairs;
};

