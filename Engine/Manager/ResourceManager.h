#pragma once
#include "Singleton.h"
#include "Image.h"
#include "SpriteAtlas.h"
#include "SpriteBaker.h"
class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;

public :
	// Preload로 원본 리소스를 불러온 뒤, 필요한 스프라이트들을 합성해 텍스처로 구워둔다.
	// Game::Init에서 이 함수 하나만 호출하면 Preload + 굽기가 한 번에 끝난다.
	void Init(Graphic& graphic);

	// 게임 시작 시 필요한 리소스를 한 번에 전부 로드한다.
	void Preload(Graphic& graphic); //메인씬 나올때 로딩씬쪽에다가 Preload로 리소스를 다 가져오자

	// 이미 로드된 리소스를 이름으로 조회만 한다 (로딩은 Preload에서만 일어난다).
	Image& GetImage(const wchar_t* fileName);
	SpriteAtlas& GetAtlas(const wchar_t* xmlPath);

	void Cleanup();

	Image& BakeImage(const wchar_t* key, Graphic& graphic, D2D1_SIZE_F size, const std::function<void(ID2D1RenderTarget*)>& drawFunc);

private :
	ResourceManager() = default;

	void loadImage(Graphic& graphic, const wchar_t* fileName);
	void loadAtlas(const wchar_t* xmlPath);

	unordered_map<wstring, unique_ptr<Image>> _images;
	unordered_map<wstring, unique_ptr<SpriteAtlas>> _atlases;

};

