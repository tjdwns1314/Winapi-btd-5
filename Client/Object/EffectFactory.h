#pragma once
#include "ObjectPool.h"
#include "EffectType.h"

class Effect;

// Effect 생성(타입 지정 + 위치 설정 + 초기화)을 한 곳에 모은다.
// Scene 등록은 호출부 책임.
class EffectFactory
{
public:
	static Effect* Create(ObjectPool<Effect>& pool, const Vector& pos, EffectType type);
};
