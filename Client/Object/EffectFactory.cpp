#include "pch.h"
#include "EffectFactory.h"
#include "Effect.h"

Effect* EffectFactory::Create(ObjectPool<Effect>& pool, const Vector& pos, EffectType type)
{
	Effect* effect = pool.Acquire();
	if (effect == nullptr)
		return nullptr;

	effect->SetEffectType(type);
	effect->SetPos(pos);
	effect->Init();
	return effect;
}
