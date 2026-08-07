#pragma once
#include "BloonType.h"
class BloonPopResolver
{
public:
	struct Result
	{
		bool hasNext = false;
		BloonColor color = BloonColor::Red;
		int32 hp = 0;
	};

	static int32 GetLayerHp(BloonColor color);
	static Result Resolve(BloonColor popedColor, int32 leftoverDamage);
};

