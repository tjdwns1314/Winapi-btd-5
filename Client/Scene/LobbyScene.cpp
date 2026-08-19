#include "pch.h"
#include "LobbyScene.h"
#include "SceneManager.h"

void LobbyScene::Init(Graphic& graphic)
{
	Super::Init(graphic);
}

void LobbyScene::Cleanup()
{
	Super::Cleanup();
}

void LobbyScene::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void LobbyScene::Render(Graphic& graphic)
{
	Super::Render(graphic);

	_ui.Render(graphic);
}

void LobbyScene::CreateUI()
{
	_ui.Init([]() { SceneManager::GetInstance().ChangeScene(SceneType::Game); });
}
