#include "pch.h"
#include "Image.h"
void Image::Load(Graphic& graphic, const wchar_t* fileName)
{
	// Graphic의 LoadBitmap을 써서 비트맵 데이터를 가져옴
	_bitmap = graphic.LoadBitmap(fileName);

	if (_bitmap == nullptr)
	{
		MessageBox(nullptr, fileName, L"LoadBitmap 실패", MB_OK);
	}
	if (_bitmap) _size = _bitmap->GetSize(); // 이미지의 가로, 세로 크기 기록
}

void Image::Draw(Graphic& graphic, float x, float y)
{
	if (!_bitmap) return;

	// (x,y) 위치부터 (x + width, y + height)까지 그릴 영역(Rect) 생성
	D2D1_RECT_F rect = D2D1::RectF(x, y, x + _size.width, y + _size.height);
	// RenderTarget에 비트맵 출력 (투명도가 들어간 PNG가 알아서 합성되어 출력됨!)
	graphic.GetRenderTarget()->DrawBitmap(_bitmap, rect);
}

void Image::DrawCell(Graphic& graphic, float destX, float destY, const CellInfo& cell)
{
	if (!_bitmap) return;

	// 아틀라스 원본 이미지에서 잘라올 영역
	D2D1_RECT_F srcRect = D2D1::RectF(cell.x, cell.y, cell.x + cell.w, cell.y + cell.h);

	// 논리 캔버스 기준 오프셋(ax, ay) 적용해서 흔들림 방지
	float drawX = destX + cell.ax;
	float drawY = destY + cell.ay;
	D2D1_RECT_F destRect = D2D1::RectF(drawX, drawY, drawX + cell.w, drawY + cell.h);

	graphic.GetRenderTarget()->DrawBitmap(
		_bitmap,
		destRect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		srcRect
	);
}

void Image::Release()
{
	// 객체가 소멸되거나 더 이상 안 쓸 때 비트맵 메모리 해제
	if (_bitmap) { _bitmap->Release(); _bitmap = nullptr; }
}