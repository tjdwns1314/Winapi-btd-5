#include "pch.h"
#include "ResourceManager.h"

void ResourceManager::Preload(Graphic& graphic)
{
	loadImage(graphic, L"Resource\\Sprite\\monkey_lane.png");
	loadAtlas(L"Resource\\Sprite\\monkey_lane.xml");

	loadImage(graphic, L"Resource\\Sprite\\InGame.png");
	loadAtlas(L"Resource\\Sprite\\InGame.xml");

	loadImage(graphic, L"Resource\\Tile\\Tile1.png");

	loadImage(graphic, L"Resource\\Sprite\\in_game_hud.png");
	loadAtlas(L"Resource\\Sprite\\in_game_hud.xml");

	loadImage(graphic, L"Resource\\Red.png");
	loadImage(graphic, L"Resource\\Blue.png");
	loadImage(graphic, L"Resource\\Green.png");
	loadImage(graphic, L"Resource\\Yellow.png");
	loadImage(graphic, L"Resource\\Pink.png");
	loadImage(graphic, L"Resource\\Black.png");
	loadImage(graphic, L"Resource\\White.png");
	loadImage(graphic, L"Resource\\Lead.png");
	loadImage(graphic, L"Resource\\Zebra.png");
	loadImage(graphic, L"Resource\\Rainbow.png");
	loadImage(graphic, L"Resource\\Ceramic.png");
}

void ResourceManager::loadImage(Graphic& graphic, const wchar_t* fileName)
{
	auto image = std::make_unique<Image>();
	image->Load(graphic, fileName);
	_images[fileName] = std::move(image);
}

void ResourceManager::loadAtlas(const wchar_t* xmlPath)
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