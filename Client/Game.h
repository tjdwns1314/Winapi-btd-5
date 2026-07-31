#pragma once

#include "Singleton.h"
#include "Image.h"
#include "Graphic.h"



// 기존 WinAPI GDI(더블 버퍼링용 HDC, HBITMAP)를 사용할 때는 
// PNG 파일의 알파 채널(투명도)을 직접 처리하기가 어렵고 번거롭습니다. 
// 그래서 Direct2D와 WIC(Windows Imaging Component)를 활용해 
// PNG의 투명 영역을 깔끔하게 불러오고 출력하는 매니저 클래스를 만드신 겁니다.

class Game : public Singleton<Game>
{
	friend Singleton<Game>;

public:
	void Init(HWND hwnd);
	void Cleanup();
	void Update();
	void Render();

	HWND GetHwnd() const { return _hwnd; }
	
private :
	Game() = default;
	~Game() = default;

private :
	HWND _hwnd = nullptr;
	RECT _rect = {};

	// 렌더링은 Direct2D가 전담하므로 GDI 백버퍼(HDC/HBITMAP)는 사용하지 않는다.
	Graphic _graphic;
};

