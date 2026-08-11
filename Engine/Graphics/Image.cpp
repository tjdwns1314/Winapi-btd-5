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

void Image::LoadFromBitmap(ID2D1Bitmap* bitmap)
{
	_bitmap = bitmap;
	if (_bitmap) _size = _bitmap->GetSize();
}

// [실제 화면용] 화면 렌더타깃을 꺼내서 아래 공용 버전으로 위임한다.
void Image::DrawSprite(Graphic& graphic, float centerX, float centerY, const CellInfo& cell, float scale, float angle, bool flipX)
{
	DrawSprite(graphic.GetRenderTarget(), centerX, centerY, cell, scale, angle, flipX);
}

void Image::Draw(Graphic& graphic, float centerX, float centerY, float scale, float angle)
{
	if (!_bitmap) return;

	// (centerX, centerY)를 이미지 중심으로 삼아 scale만큼 확대/축소해서 그림
	const float width = _size.width * scale;
	const float height = _size.height * scale;
	const float x = centerX - width * 0.5f;
	const float y = centerY - height * 0.5f;

	D2D1_RECT_F rect = D2D1::RectF(x, y, x + width, y + height);

	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	// (centerX, centerY)를 축으로 angle(도, 시계방향)만큼 회전시킨 뒤 그림
	renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY)));
	// RenderTarget에 비트맵 출력 (투명도가 들어간 PNG가 알아서 합성되어 출력됨!)
	renderTarget->DrawBitmap(_bitmap, rect);
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

// [공용/임시 도화지용] 실제로 DrawBitmap을 호출하는 본체.
// renderTarget으로 화면(ID2D1HwndRenderTarget)과 임시 텍스처(ID2D1BitmapRenderTarget)를
// 구분 없이 받을 수 있어서, BakeImage로 굽는 용도로도 그대로 재사용된다.
void Image::DrawSprite(ID2D1RenderTarget* renderTarget, float centerX, float centerY, const CellInfo& cell, float scale, float angle, bool flipX)
{
	if (!_bitmap) return;

	// 아틀라스 원본 이미지에서 잘라올 영역
	D2D1_RECT_F srcRect = D2D1::RectF(cell.x, cell.y, cell.x + cell.w, cell.y + cell.h);

	// 트림 전 원본 스프라이트 크기(aw, ah) 기준으로 중심을 잡고,
	// 트림 오프셋(ax, ay)만큼 되돌려서 실제 그릴 위치를 구한다.
	const float originX = centerX - cell.aw * scale * 0.5f;
	const float originY = centerY - cell.ah * scale * 0.5f;
	const float drawX = originX + cell.ax * scale;
	const float drawY = originY + cell.ay * scale;

	D2D1_RECT_F destRect = D2D1::RectF(drawX, drawY, drawX + cell.w * scale, drawY + cell.h * scale);

	D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Identity();
	if (flipX)
		transform = transform *
		D2D1::Matrix3x2F::Scale(D2D1::SizeF(-1.0f, 1.0f),
			D2D1::Point2F(centerX, centerY));
	transform = transform * D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(centerX, centerY));
	renderTarget->SetTransform(transform);
	renderTarget->DrawBitmap(
		_bitmap,
		destRect,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		srcRect
	);

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Image::Release()
{
	// 객체가 소멸되거나 더 이상 안 쓸 때 비트맵 메모리 해제
	if (_bitmap) { _bitmap->Release(); _bitmap = nullptr; }
}