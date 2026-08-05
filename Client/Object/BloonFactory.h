#pragma once
#include "BloonType.h"

class Bloon;

// Bloon 생성 + 초기화(색상별 이미지/스탯 조립)을 한 곳에 모은다.
// Scene 등록은 호출부 책임.
class BloonFactory
{
public:
	static Bloon* Create(BloonColor color, const Vector& pos, const vector<Vector>* path);
};
