#pragma once
#include "Graphic.h"
#include "SpriteAtlas.h"

// Graphic이 엔진 전체 판을 관리한다면, 
// Image는 맵 객체, 캐릭터, 풍선 등 낱개의 PNG 이미지 하나하나를 객체화한 것입니다.

class Image
{
public:
	void Load(Graphic& graphic, const wchar_t* fileName);
	// 오프스크린 렌더타깃에서 이미 합성해둔 비트맵을 그대로 받아 Image로 감싼다.
	void LoadFromBitmap(ID2D1Bitmap* bitmap);
	void Draw(Graphic& graphic, float centerX, float centerY, float scale = 1.0f, float angle = 0.0f);
	void Release();

	// [실제 화면용] 매 프레임 화면(HWND 렌더타깃)에 스프라이트를 그릴 때 사용.
	void DrawSprite(Graphic& graphic, float centerX, float centerY, const CellInfo& cell, float scale = 1.0f, float angle = 0.0f, bool flipX = false);
	// [공용/임시 도화지용] 화면이든 임시 오프스크린 텍스처든, 렌더타깃을 직접 지정해서 그릴 때 사용.
	// 위 Graphic& 버전이 내부적으로 이 함수를 호출한다.
	void DrawSprite(ID2D1RenderTarget* renderTarget, float centerX, float centerY, const CellInfo& cell, float scale = 1.0f, float angle = 0.0f, bool flipX = false);
	D2D1_SIZE_F GetSize() const { return _size; }
private:
	// 변환이 완료된 Direct2D 그래픽 데이터(비트맵) 주소입니다.
	ID2D1Bitmap* _bitmap = nullptr;
	// 원본 PNG 이미지의 가로/세로 크기(Width,Height)를 저장하는 구조체입니다.
	D2D1_SIZE_F _size = {};
};

