#include "pch.h"
#include "SpriteBaker.h"
#include "ResourceManager.h"


void SpriteBaker::composeFrame(ID2D1RenderTarget* rt, D2D1_SIZE_F size, const BakeFrame& parts)
{
	// 한꺼번에 그릴 전체 캔버스 사이즈 = 스프라이트의 실제 크기에서 딱 절반(가로),(세로)
	const float cx = size.width * 0.5f;
	const float cy = size.height * 0.5f;

	for (const BakePart& part : parts)
	{
		const CellInfo* cell =
			_atlas.GetCell(part.cellName);
		if (!cell)
		{
		#ifdef _DEBUG
			wchar_t debugBuf[256];
			swprintf_s(debugBuf, L"[SpriteBaker] Warning: Cell '%S' not found in atlas.\n", part.cellName);
			OutputDebugString(debugBuf);
		#endif
			continue;
		}

		// 개별 부품 이미지의 원래 크기
		// cell->aw (아틀라스에 등록된 원본 이미지의 원래 너비)
		// cell->ah (아틀라스에 등록된 원본 이미지의 원래 높이)

		// 크기 조정(Scale)이 반영된 스프라이트의 실제 크기에서 딱 절반(가로/세로)의 길이를 구하는 과정
		const float halfW = (cell->aw * part.scale) * 0.5f;
		const float halfH = (cell->ah * part.scale) * 0.5f;

		float anchorX = cx;
		float anchorY = cy;

		switch (part.anchor)
		{
		case BakeAnchor::Left:        anchorX = cx - halfW; break;
		case BakeAnchor::Right:       anchorX = cx + halfW; break;
		case BakeAnchor::Top:         anchorY = cy - halfH; break;
		case BakeAnchor::Bottom:      anchorY = cy + halfH; break;
		case BakeAnchor::TopLeft:     anchorX = cx - halfW; anchorY = cy - halfH; break;
		case BakeAnchor::TopRight:    anchorX = cx + halfW; anchorY = cy - halfH; break;
		case BakeAnchor::BottomLeft:  anchorX = cx - halfW; anchorY = cy + halfH; break;
		case BakeAnchor::BottomRight: anchorX = cx + halfW; anchorY = cy + halfH; break;
		default: break; // Center
		}
		_sheet.DrawSprite(rt, anchorX + part.offset.x, anchorY + part.offset.y, *cell, part.scale, part.angle, part.flipX);
	}
}


void SpriteBaker::Bake(ResourceManager& res, Graphic& graphic, const wchar_t* key, D2D1_SIZE_F size, const BakeFrame& parts)
{
	res.BakeImage(key, graphic, size, [this, size, &parts](ID2D1RenderTarget* rt)
		{
			composeFrame(rt, size, parts);
		});
}

void SpriteBaker::BakeAnimation(ResourceManager& res, Graphic& graphic, const wchar_t* keyPrefix, D2D1_SIZE_F size, const std::vector<BakeFrame>& frames)
{
	for (size_t i = 0; i < frames.size(); ++i)
	{
		wchar_t key[128];
		swprintf_s(key, L"%s_%02d", keyPrefix, static_cast<int>(i + 1));
		Bake(res, graphic, key, size, frames[i]);
	}
}

