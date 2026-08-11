#include "pch.h"
#include "Graphic.h"
void Graphic::Init(HWND hwnd)
{

	if (hwnd == nullptr)
	{
		MessageBox(nullptr, L"hwnd == nullptr", L"Error", MB_OK);
		return;
	}

	if (!IsWindow(hwnd))
	{
		MessageBox(nullptr, L"hwnd가 유효한 Window가 아닙니다.", L"Error", MB_OK);
		return;
	}

	// 1. COM 라이브러리 초기화 (WIC, DIrect2D 기능 사용 준비)
	HRESULT hr = CoInitialize(nullptr);
	if (FAILED(hr))
	{
		// 필요하면 에러 처리 / 로그
		return;
	}

	// 2. Direct2D 공장 객체 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_factory);
	if (FAILED(hr)) return;

	// 3. WIC(이미지 로더) 공장 객체 생성
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_wicFactory));
	if (FAILED(hr)) return;

	// 4. 창 크기에 맞춰 Direct2D용 그려질 도화지(_renderTarget) 생성
	RECT rc;
	GetClientRect(hwnd, &rc); // 창의 내부 크기를 구해옴

	hr = _factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom)),
		&_renderTarget);
	if (FAILED(hr)) return;

	// 5. 재사용할 브러시 하나를 미리 만들어둔다. (색은 GetBrush에서 교체)
	_renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &_brush);
}

ID2D1SolidColorBrush* Graphic::GetBrush(const D2D1::ColorF& color)
{
	if (_brush == nullptr)
		return nullptr;

	_brush->SetColor(color);
	return _brush;
}

ID2D1BitmapRenderTarget* Graphic::CreateOffscreenRenderTarget(D2D1_SIZE_F size)
{
	ID2D1BitmapRenderTarget* target = nullptr;
	_renderTarget->CreateCompatibleRenderTarget(size, &target);
	return target;
}

void Graphic::BeginDraw() { _renderTarget->BeginDraw(); }
void Graphic::EndDraw() { _renderTarget->EndDraw(); }
void Graphic::Clear(D2D1::ColorF color) { _renderTarget->Clear(color); }

void Graphic::Cleanup()
{
	// COM 객체는 delete가 아니라 Release로 해제한다.
	if (_brush)
	{
		_brush->Release();
		_brush = nullptr;
	}

	if (_wicFactory)
	{
		_wicFactory->Release();
		_wicFactory = nullptr;
	}

	if (_renderTarget)
	{
		_renderTarget->Release();
		_renderTarget = nullptr;
	}

	if (_factory)
	{
		_factory->Release();
		_factory = nullptr;
	}
	CoUninitialize();
}

ID2D1Bitmap* Graphic::LoadBitmap(const wchar_t* fileName)
{
	IWICBitmapDecoder* decoder = nullptr;
	HRESULT hr = _wicFactory->CreateDecoderFromFilename(
		fileName, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
	if (FAILED(hr))
	{
		OutputDebugString(L"[LoadBitmap] 파일을 찾을 수 없음: ");
		OutputDebugString(fileName);
		OutputDebugString(L"\n");
		return nullptr;
	}

	IWICBitmapFrameDecode* frame = nullptr;
	hr = decoder->GetFrame(0, &frame);
	if (FAILED(hr)) { decoder->Release(); return nullptr; }

	IWICFormatConverter* converter = nullptr;
	hr = _wicFactory->CreateFormatConverter(&converter);
	if (FAILED(hr)) { frame->Release(); decoder->Release(); return nullptr; }

	hr = converter->Initialize(
		frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone,
		nullptr, 0.f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr)) { converter->Release(); frame->Release(); decoder->Release(); return nullptr; }

	ID2D1Bitmap* bitmap = nullptr;
	hr = _renderTarget->CreateBitmapFromWicBitmap(converter, nullptr, &bitmap);

	converter->Release();
	frame->Release();
	decoder->Release();

	if (FAILED(hr)) return nullptr;
	return bitmap;
}
