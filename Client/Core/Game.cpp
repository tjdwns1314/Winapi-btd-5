#include "pch.h"
#include "Game.h"
#include "Graphic.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Scene/GameScene.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC(이미지 로더) 관련 함수도 쓰고 있으므로 같이 필요
#pragma comment(lib, "ole32.lib")

void Game::Init(HWND hwnd)
{
	// 윈도우 창
	_hwnd = hwnd;

	// 현재 창의 내부 크기(너비, 높이) 구하기
	GetClientRect(hwnd, &_rect);

	_graphic.Init(hwnd);

	TimeManager::GetInstance().Init();
	InputManager::GetInstance().Init(hwnd);

	// 게임 시작 시 필요한 이미지/아틀라스 리소스를 한 번에 전부 로드한다.
	// 이후 개별 객체는 ResourceManager::GetImage/GetAtlas로 조회만 한다.
	ResourceManager::GetInstance().Preload(_graphic);

	// 씬 생성/등록은 Client가 담당한다. (Engine은 구체 씬을 알지 못함)
	SceneManager& sceneManager = SceneManager::GetInstance();
	sceneManager.Init(_graphic);
	sceneManager.RegisterScene(SceneType::Game, new GameScene());
	sceneManager.ChangeScene(SceneType::Game);
}

void Game::Cleanup()
{
	SceneManager::GetInstance().Cleanup();
	_graphic.Cleanup();
}

void Game::Update()
{
	TimeManager& timeManager = TimeManager::GetInstance();
	timeManager.Update();
	InputManager::GetInstance().Update();

	SceneManager::GetInstance().Update(timeManager.GetDT());
}

void Game::Render()
{
	_graphic.BeginDraw();
	_graphic.Clear(D2D1::ColorF(D2D1::ColorF::Black));

	SceneManager::GetInstance().Render(_graphic);

	_graphic.EndDraw();
}
