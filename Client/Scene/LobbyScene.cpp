#include "pch.h"
#include "LobbyScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "SaveManager.h"
#include "AudioManager.h"

void LobbyScene::Init(Graphic& graphic)
{
	Super::Init(graphic);

	AudioManager::GetInstance().PlayBgm(L"main");
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
		[]() // 새 게임: 기존 자동저장이 남아있으면 다음에 "게임 재개"가 그 파일을 그대로 불러오게 되므로, 전환 전에 지운다.
		{
			SaveManager::DeleteFile(GameScene::kSaveFilePath);
			SceneManager::GetInstance().ChangeScene(SceneType::Game);
		},
		[]() // 게임 재개: 저장 파일을 먼저 읽어 pending 상태로 만든 뒤 전환해야 Init()이 그 데이터를 반영한다.
		{
			GameScene* gameScene = static_cast<GameScene*>(SceneManager::GetInstance().GetScene(SceneType::Game));
			if (gameScene != nullptr && gameScene->PrepareLoad(GameScene::kSaveFilePath))
				SceneManager::GetInstance().ChangeScene(SceneType::Game);
		},
		[]() { return SaveManager::FileExists(GameScene::kSaveFilePath); }); // 팝업 열릴 때마다 "게임 재개" 활성화 여부 판단용
}
