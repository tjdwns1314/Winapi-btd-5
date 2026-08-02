#include "pch.h"
#include "SceneManager.h"
#include "Scene/Scene.h"

void SceneManager::Init(Graphic& graphic)
{
	_graphic = &graphic;
}

void SceneManager::Cleanup()
{
	for (int32 i = 0; i < static_cast<int32>(SceneType::Max); ++i)
	{
		if (_scenes[i] == nullptr)
			continue;

		_scenes[i]->Cleanup();
		delete _scenes[i];
		_scenes[i] = nullptr;
	}

	_currentScene = nullptr;
	_reservedScene = SceneType::Max;
	_graphic = nullptr;
}

void SceneManager::RegisterScene(SceneType sceneType, Scene* scene)
{
	if (scene == nullptr || sceneType >= SceneType::Max)
		return;

	int32 index = static_cast<int32>(sceneType);

	// 같은 자리에 이미 씬이 있으면 교체 전에 정리한다.
	if (_scenes[index] != nullptr)
	{
		_scenes[index]->Cleanup();
		delete _scenes[index];
	}

	_scenes[index] = scene;
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (sceneType >= SceneType::Max)
		return;

	_reservedScene = sceneType;
}

void SceneManager::ApplyReservedScene()
{
	if (_reservedScene >= SceneType::Max)
		return;

	Scene* next = _scenes[static_cast<int32>(_reservedScene)];
	_reservedScene = SceneType::Max;

	// 등록되지 않은 씬으로는 전환하지 않는다.
	if (next == nullptr || next == _currentScene)
		return;

	if (_currentScene != nullptr)
		_currentScene->Cleanup();

	_currentScene = next;

	if (_graphic != nullptr)
		_currentScene->Init(*_graphic);
}

void SceneManager::Update(float deltaTime)
{
	// 씬 전환은 프레임 경계에서만 일어나도록 갱신 전에 처리한다.
	ApplyReservedScene();

	if (_currentScene == nullptr)
		return;

	_currentScene->Update(deltaTime);
	_currentScene->PostUpdate();
}

void SceneManager::Render(Graphic& graphic)
{
	if (_currentScene == nullptr)
		return;

	_currentScene->Render(graphic);
}