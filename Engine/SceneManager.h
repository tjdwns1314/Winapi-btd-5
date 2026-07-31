#pragma once
#include "Singleton.h"

class Scene;
class Graphic;

// 씬 등록/전환/갱신을 담당한다.
// Engine 레이어이므로 Client의 구체 씬(GameScene 등)을 직접 알지 않는다.
// 씬 생성과 등록은 Client(Game::Init)에서 수행한다.
class SceneManager : public Singleton<SceneManager>
{
	// Singleton 객체를 '친구'로 선언해서 private 접근 가능하게 열어준다.
	friend Singleton<SceneManager>;

public:
	void Init(Graphic& graphic);
	void Cleanup();

	void Update(float deltaTime);
	void Render(Graphic& graphic);

	// 등록된 씬의 소유권은 SceneManager가 가진다. (Cleanup에서 delete)
	void RegisterScene(SceneType sceneType, Scene* scene);

	// 프레임 도중 씬을 바꾸면 순회 중인 컨테이너가 파괴되므로,
	// 예약만 해두고 실제 전환은 다음 Update 시작 시점에 수행한다.
	void ChangeScene(SceneType sceneType);

	Scene* GetCurrentScene() const { return _currentScene; }

private:
	// 아무나 생성못하게 생성자/소멸자를 숨기자
	SceneManager() = default;
	~SceneManager() = default;

	void ApplyReservedScene();

	Graphic* _graphic = nullptr;
	Scene* _scenes[static_cast<int32>(SceneType::Max)] = {};
	Scene* _currentScene = nullptr;
	SceneType _reservedScene = SceneType::Max;
};

