#include "pch.h"
#include "ResourceManager.h"

void ResourceManager::LoadImage(Graphic& graphic, const wchar_t* fileName)
{
	auto image = std::make_unique<Image>();
	image->Load(graphic, fileName);
	_images[fileName] = std::move(image);
}

void ResourceManager::LoadAtlas(const wchar_t* xmlPath)
{
	auto atlas = std::make_unique<SpriteAtlas>();
	atlas->LoadXml(xmlPath);
	_atlases[xmlPath] = std::move(atlas);
}

Image& ResourceManager::GetImage(const wchar_t* fileName)
{
	auto it = _images.find(fileName);
	if (it == _images.end())
	{
		MessageBox(nullptr, fileName, L"GetImage 실패: Preload 되지 않은 리소스", MB_OK);
		static Image dummy;
		return dummy;
	}
	return *it->second;
}

SpriteAtlas& ResourceManager::GetAtlas(const wchar_t* xmlPath)
{
	auto it = _atlases.find(xmlPath);
	if (it == _atlases.end())
	{
		MessageBox(nullptr, xmlPath, L"GetAtlas 실패: Preload 되지 않은 리소스", MB_OK);
		static SpriteAtlas dummy;
		return dummy;
	}
	return *it->second;
}

void ResourceManager::Cleanup()
{
	for (auto& [name, image] : _images)
		image->Release();

	_images.clear();
	_atlases.clear();
}

Image& ResourceManager::BakeImage(const wchar_t* key, Graphic& graphic, D2D1_SIZE_F size,
	const std::function<void(ID2D1RenderTarget*)>& drawFunc)
{
	// 1. 메모리 상에 size 크기의 임시 렌더 타깃(오프스크린 도화지)을 생성합니다.
	ID2D1BitmapRenderTarget* offscreen = graphic.CreateOffscreenRenderTarget(size);

	// 2. 임시 렌더 타깃에 그리기 시작을 알립니다.
	offscreen->BeginDraw();

	// 3. 도화지 배경을 완전 투명(Alpha = 0.0f)으로 깔끔하게 지웁니다.
	offscreen->Clear(D2D1::ColorF(0, 0, 0, 0.0f));

	// 4. 인자로 전달받은 함수(드로우 콜백)에 임시 렌더 타깃을 넘겨 실행시킵니다.
	//    호출하는 곳에서는 이 렌더 타깃 위에 여러 이미지나 도형을 겹쳐 그리는 코드를 작성하게 됩니다.
	drawFunc(offscreen);

	// 5. 그리기가 완료되었음을 선언합니다.
	offscreen->EndDraw();

	// 6. 임시 렌더 타깃에 그려진 최종 결과물을 비트맵(ID2D1Bitmap) 객체로 추출합니다.
	ID2D1Bitmap* bitmap = nullptr;
	offscreen->GetBitmap(&bitmap);

	// 7. 더 이상 그릴 필요가 없는 임시 렌더 타깃(도화지 자체)은 메모리에서 해제합니다.
	offscreen->Release();

	// 8. 엔진 내부의 Image 클래스 인스턴스를 동적으로 생성하고, 구워진 비트맵 데이터를 로드합니다.
	auto image = std::make_unique<Image>();
	image->LoadFromBitmap(bitmap);

	// 9. 완성된 Image 객체를 ResourceManager 내부의 이미지 맵(_images)에 고유 이름(key)으로 등록합니다.
	_images[key] = std::move(image);

	// 10. 이후 바로 사용 가능하도록 등록된 이미지 객체의 참조를 반환합니다.
	return *_images[key];
}
