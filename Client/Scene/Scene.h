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

    // 주요 생명주기
    virtual void Init(Graphic& graphic);
    virtual void Cleanup();
    virtual void Update(float deltaTime);
    virtual void Render(Graphic& graphic);
    void PostUpdate();

    // 액터 & 작업 관리
    void AddActor(Actor* actor);
    const vector<Actor*>& GetActors(RenderLayer layer) const { return _actors[static_cast<int32>(layer)]; }
    void AddPostUpdateAction(function<void()> action);

    // Getter / Setter
    SceneType GetSceneType() const { return _sceneType; }

protected:
    // 씬마다 필요한 UI를 이 시점에 만들어 등록한다.
    // Engine은 Client UI를 모르므로 기본은 아무것도 하지 않고, 파생 씬이 override한다.
    virtual void CreateUI() {}
    CollisionManager& GetCollisionManager() { return _collisionManager; }

protected:
    // 씬 정보
    SceneType _sceneType = SceneType::Max;

    // 액터 및 예약 작업
    vector<Actor*> _actors[static_cast<int32>(RenderLayer::Count)];
    vector<function<void()>> _postUpdateActions;

    // 충돌 관리
    CollisionManager _collisionManager;

private:
    // Update/Render가 공통으로 쓰는 "레이어 순회 + 활성 액터만 걸러서 action 실행" 로직.
    void forEachActiveActor(function<void(Actor*)> action);
};