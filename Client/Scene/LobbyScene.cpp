#include "pch.h"
#include "LobbyScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "SaveManager.h"

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
	_ui.Init(
		[]() { SceneManager::GetInstance().ChangeScene(SceneType::Game); }, // 새 게임: pending load 없이 바로 진입 → Init()이 기본값으로 새로 시작
		[]() // 게임 재개: 저장 파일을 먼저 읽어 pending 상태로 만든 뒤 전환해야 Init()이 그 데이터를 반영한다.
		{
			GameScene* gameScene = static_cast<GameScene*>(SceneManager::GetInstance().GetScene(SceneType::Game));
			if (gameScene != nullptr && gameScene->PrepareLoad(GameScene::kSaveFilePath))
				SceneManager::GetInstance().ChangeScene(SceneType::Game);
		},
		[]() { return SaveManager::FileExists(GameScene::kSaveFilePath); }); // 팝업 열릴 때마다 "게임 재개" 활성화 여부 판단용
}
