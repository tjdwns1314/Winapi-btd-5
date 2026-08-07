#pragma once

#include "CollisionManager.h"
class Actor;
class Graphic;

// 씬 하나가 소유한 액터들을 레이어 순서대로 갱신/렌더링한다.
// 게임 고유 로직은 Client의 파생 씬(GameScene 등)이 담당한다.
class Scene
{
public:
	Scene(SceneType sceneType) : _sceneType(sceneType) {}
	virtual ~Scene();

	// 리소스 로드에 Graphic이 필요하므로 함께 넘긴다.
	virtual void Init(Graphic& graphic);
	virtual void Cleanup();

	virtual void Update(float deltaTime);
	virtual void Render(Graphic& graphic);

	void AddActor(Actor* actor);

	// 사거리 탐색, 충돌 판정 등에서 레이어별 액터 목록을 읽기 전용으로 조회할 때 사용한다.
	const vector<Actor*>& GetActors(RenderLayer layer) const { return _actors[static_cast<int32>(layer)]; }

	// 프레임 도중 컨테이너를 건드리지 않기 위해, 죽은 액터 정리와
	// 예약된 작업은 모두 프레임 끝(PostUpdate)에서 처리한다.
	void PostUpdate();
	void AddPostUpdateAction(function<void()> action);

	SceneType GetSceneType() const { return _sceneType; }

protected:
	// 씬마다 필요한 UI를 이 시점에 만들어 등록한다.
	// Engine은 Client UI를 모르므로 기본은 아무것도 하지 않고, 파생 씬이 override한다.
	virtual void CreateUI() {}

	SceneType _sceneType = SceneType::Max;

	// RenderLayer 순서대로 그리기 위해 레이어별로 나눠서 보관한다.
	vector<Actor*> _actors[static_cast<int32>(RenderLayer::Count)];
	vector<function<void()>> _postUpdateActions;

	CollisionManager& GetCollisionManager()
	{
		return _collisionManager;
	}

	CollisionManager _collisionManager;
};

