#pragma once
#include "Singleton.h"
#include "Image.h"
#include "SpriteAtlas.h"
#include "SpriteBaker.h"
class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;

public :
	void LoadImage(Graphic& graphic, const wchar_t* fileName);
	void LoadAtlas(const wchar_t* xmlPath);

	Image& GetImage(const wchar_t* fileName);
	SpriteAtlas& GetAtlas(const wchar_t* xmlPath);

	void Cleanup();

	Image& BakeImage(const wchar_t* key, Graphic& graphic, D2D1_SIZE_F size, const std::function<void(ID2D1RenderTarget*)>& drawFunc);

private :
	ResourceManager() = default;

	unordered_map<wstring, unique_ptr<Image>> _images;
	unordered_map<wstring, unique_ptr<SpriteAtlas>> _atlases;

};

