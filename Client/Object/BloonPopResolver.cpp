#include "pch.h"
#include "BloonPopResolver.h"

int32 BloonPopResolver::GetLayerHp(BloonColor color)
{
	switch (color)
	{
	case BloonColor::Ceramic:
		return 10;
	default:
		return 1;
	}
}






