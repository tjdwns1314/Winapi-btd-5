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

	// 브러시는 생성 비용이 크므로 하나만 만들어두고 색만 바꿔 재사용한다.
	// 디버그용 그리드/경로 렌더, 타워 사거리 표시 등에 사용.
	ID2D1SolidColorBrush* GetBrush(const D2D1::ColorF& color);

private:
	// Direct2D 객체들을 생성해주는 공장
	ID2D1Factory* _factory = nullptr;
	// 윈도우 창(HWND)에 직접 그릴 실제 도화지 판
	ID2D1HwndRenderTarget* _renderTarget = nullptr;
	// WIC 공장. PNG,JPG같은 이미지파일 해석기를 만드는 도구
	IWICImagingFactory* _wicFactory = nullptr;
	// 재사용 브러시. 매 프레임 생성하지 않기 위해 캐싱한다.
	ID2D1SolidColorBrush* _brush = nullptr;
};

