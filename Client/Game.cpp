#include "pch.h"
#include "Game.h"
#include "Graphic.h"
#include "TimeManager.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib") // WIC(이미지 로더) 관련 함수도 쓰고 있으므로 같이 필요
#pragma comment(lib, "ole32.lib")

void Game::Init(HWND hwnd)
{
	// 윈도우 창
	_hwnd = hwnd;

	// 실제화면
	_hdc = GetDC(hwnd);

	// 백버퍼 메모리
	_hdcBack = CreateCompatibleDC(_hdc);

	// 현재 창의 내부 크기(너비, 높이) 구하기
	GetClientRect(hwnd, &_rect);

	// 화면 DC와 호환되는 '비트맵' 생성 
	_bmpBack = CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);

	// 메모리 DC에 비트맵을 연결하기
	HBITMAP prev = (HBITMAP)SelectObject(_hdcBack, _bmpBack);
	// 연결 직후 튕겨져 나온 기본 빈 1x1 비트맵 삭제
	DeleteObject(prev);

	_graphic.Init(hwnd);
	_gameScene.Init(_graphic);

	TimeManager::GetInstance().Init();
}

void Game::Cleanup()
{
	_gameScene.Release();
	_graphic.Cleanup();
}

void Game::Update()
{
	TimeManager::GetInstance().Update();
	_gameScene.Update();
}

void Game::Render()
{
	_graphic.BeginDraw();
	_graphic.Clear(D2D1::ColorF(D2D1::ColorF::Black));

	_gameScene.Render(_graphic);
	_graphic.EndDraw();
}
