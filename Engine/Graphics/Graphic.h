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
	void Resize(uint32 width, uint32 height);
	ID2D1HwndRenderTarget* GetRenderTarget() {return _renderTarget;}

	// 브러시는 생성 비용이 크므로 하나만 만들어두고 색만 바꿔 재사용한다.
	// 디버그용 그리드/경로 렌더, 타워 사거리 표시 등에 사용.
	ID2D1SolidColorBrush* GetBrush(const D2D1::ColorF& color);

	// 메인 화면과 별개로, 지정한 크기만큼의 임시 도화지(오프스크린 렌더타깃)을 만든다.
	// 여기에 스프라이트를 미리 합성해두면, 이후에는 완성된 비트맵 하나만 그리면 된다.
	ID2D1BitmapRenderTarget* CreateOffscreenRenderTarget(D2D1_SIZE_F size);

	void DrawString(const wchar_t* text, D2D1_RECT_F layoutRect, FontSize size,
		D2D1::ColorF color, DWRITE_TEXT_ALIGNMENT align =
		DWRITE_TEXT_ALIGNMENT_LEADING,
		DWRITE_PARAGRAPH_ALIGNMENT vAlign = DWRITE_PARAGRAPH_ALIGNMENT_NEAR);


private:
	// Direct2D 객체들을 생성해주는 공장
	ID2D1Factory* _factory = nullptr;
	// 윈도우 창(HWND)에 직접 그릴 실제 도화지 판
	ID2D1HwndRenderTarget* _renderTarget = nullptr;
	// WIC 공장. PNG,JPG같은 이미지파일 해석기를 만드는 도구
	IWICImagingFactory* _wicFactory = nullptr;
	// 재사용 브러시. 매 프레임 생성하지 않기 위해 캐싱한다.
	ID2D1SolidColorBrush* _brush = nullptr;

	IDWriteFactory* _dwriteFactory = nullptr;
	unordered_map<FontSize, IDWriteTextFormat*> _textFormats;
	IDWriteTextFormat* GetTextFormat(FontSize size);
};

