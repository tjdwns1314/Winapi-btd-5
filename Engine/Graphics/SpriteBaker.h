#pragma once
#include <vector>
#include "Image.h"
#include "SpriteAtlas.h"

class ResourceManager;

enum class BakeAnchor
{
	Center,
	Left,Right,Top,Bottom,
	TopLeft,TopRight,BottomLeft,BottomRight
};

struct BakePart
{
	const char* cellName;
	BakeAnchor anchor = BakeAnchor::Center;
	D2D1_POINT_2F offset = { 0.0f, 0.0f };
	float angle = 0.0f;
	float scale = 1.0f;
	bool flipX = false;
};

using BakeFrame = std::vector<BakePart>;

class SpriteBaker
{
public:
	SpriteBaker(Image& sheet, SpriteAtlas& atlas)
		:_sheet(sheet), _atlas(atlas) {}
	void Bake(ResourceManager& res, Graphic& graphic, const wchar_t* key, D2D1_SIZE_F size, const BakeFrame& parts);
	void BakeAnimation(ResourceManager& res, Graphic& graphic, const wchar_t* keyPrefix, D2D1_SIZE_F size, const std::vector<BakeFrame>& frames);
private:
	void composeFrame(ID2D1RenderTarget* rt, D2D1_SIZE_F size, const BakeFrame& parts);
	Image& _sheet;
	SpriteAtlas& _atlas;
};
