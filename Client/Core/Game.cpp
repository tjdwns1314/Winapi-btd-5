#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "GameAssets.h"
#include "InputManager.h"
#include "Scene/GameScene.h"
#include "Scene/EditorScene.h"
#include "Scene/LobbyScene.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC(이미지 로더) 관련 함수도 쓰고 있으므로 같이 필요
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "dwrite.lib")

void Game::Init(HWND hwnd)
{
	// 윈도우 창
	_hwnd = hwnd;

	// 현재 창의 내부 크기(너비, 높이) 구하기
	GetClientRect(hwnd, &_rect);

	_graphic.Init(hwnd);

	TimeManager::GetInstance().Init();
	InputManager::GetInstance().Init(hwnd);
	AudioManager::GetInstance().Init();

	// 로딩 화면 이미지만 먼저 로드해서 한 번 그려준다.
	// (아래 GameAssets::Load가 끝날 때까지 하얀 화면으로 멈춰있는 문제를 없애기 위함)
	ResourceManager::GetInstance().LoadImage(_graphic, L"Resource\\Sprite\\newslocal_01.png");
	drawLoadingScreen();

	// 게임 시작 시 필요한 이미지/아틀라스 리소스를 한 번에 전부 로드한다.
	// 이후 개별 객체는 ResourceManager::GetImage/GetAtlas로 조회만 한다.
	GameAssets::Load(_graphic);

	// 씬 생성/등록은 Client가 담당한다. (Engine은 구체 씬을 알지 못함)
	SceneManager& sceneManager = SceneManager::GetInstance();
	sceneManager.Init(_graphic);
	sceneManager.RegisterScene(SceneType::Game, new GameScene());
	sceneManager.RegisterScene(SceneType::Editor, new EditorScene());
	sceneManager.RegisterScene(SceneType::Lobby, new LobbyScene());
	sceneManager.ChangeScene(SceneType::Lobby);
}

void Game::Cleanup()
{
	SceneManager::GetInstance().Cleanup();
	ResourceManager::GetInstance().Cleanup();
	AudioManager::GetInstance().Cleanup();
	_graphic.Cleanup();
}

void Game::Update(float deltaTime)
{
	TimeManager::GetInstance().Update(deltaTime);
	InputManager::GetInstance().Update();
	AudioManager::GetInstance().Update();

	SceneManager::GetInstance().Update(deltaTime);

	if (InputManager::GetInstance().GetButtonDown(KeyType::F1))
	{
		SceneManager& sceneManager = SceneManager::GetInstance();
		Scene* current = sceneManager.GetCurrentScene();
		const bool isEditor = current != nullptr &&
			current->GetSceneType() == SceneType::Editor;
		sceneManager.ChangeScene(isEditor ? SceneType::Game : SceneType::Editor);

	}
}

void Game::Render()
{
	_graphic.BeginDraw();
	_graphic.Clear(D2D1::ColorF(D2D1::ColorF::Black));

	SceneManager::GetInstance().Render(_graphic);

	_graphic.EndDraw();
}

void Game::OnResize(uint32 width, uint32 height)
{
	_graphic.Resize(width, height);
}

// Game::drawLoadingScreen
// 검은 배경 위에 newslocal_01 이미지를 화면 중앙에 한 프레임 그려서 표시한다.
void Game::drawLoadingScreen()
{
	Image& loadingImage = ResourceManager::GetInstance().GetImage(L"Resource\\Sprite\\newslocal_01.png");

	_graphic.BeginDraw();
	_graphic.Clear(D2D1::ColorF(D2D1::ColorF::Black));

	const float centerX = static_cast<float>(GWinSizeX) * 0.5f;
	const float centerY = static_cast<float>(GWinSizeY) * 0.5f;
	loadingImage.Draw(_graphic, centerX, centerY,1.5f);

	_graphic.EndDraw();
}
