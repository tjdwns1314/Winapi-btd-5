#pragma once
class Graphic
{
public :
	void Init(HWND hwnd);
	void Cleanup();
	ID2D1Bitmap* LoadBitmap(const wchar_t* fileName);
	void BeginDraw();
	void EndDraw();
	void Clear(D2D1::ColorF color);
	ID2D1HwndRenderTarget* GetRenderTarget() {return _renderTarget;}
private:
	// Direct2D 객체들을 생성해주는 공장
	ID2D1Factory* _factory;
	// 윈도우 창(HWND)에 직접 그릴 실제 도화지 판
	ID2D1HwndRenderTarget* _renderTarget;
	// WIC 공장. PNG,JPG같은 이미지파일 해석기를 만드는 도구
	IWICImagingFactory* _wicFactory;
};

