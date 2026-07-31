#pragma once
#include "Graphic.h"
#include "Sprite.h"

// Graphic이 엔진 전체 판을 관리한다면, 
// Image는 맵 객체, 캐릭터, 풍선 등 낱개의 PNG 이미지 하나하나를 객체화한 것입니다.

class Image
{
public:
	void Load(Graphic& graphic, const wchar_t* fileName);
	void Draw(Graphic& graphic, float x, float y);
	void Release();
	void DrawCell(Graphic& graphic, float x, float y, const CellInfo& cell);
private:
	// 변환이 완료된 Direct2D 그래픽 데이터(비트맵) 주소입니다.
	ID2D1Bitmap* _bitmap = nullptr;
	// 원본 PNG 이미지의 가로/세로 크기(Width,Height)를 저장하는 구조체입니다.
	D2D1_SIZE_F _size = {};
};

