#include "pch.h"
#include "EffectType.h"

const EffectData& GetEffectData(EffectType type)
{
	static const unordered_map<EffectType, EffectData> table =
	{
		{ EffectType::Pop,       EffectData{ { "pop" }, 0.05f, 1.0f } },
		{ EffectType::Explosion, EffectData{ { "explosion_01", "explosion_02", "explosion_05", "explosion_06" }, 0.04f, 0.3f } },
	};
	auto it = table.find(type);
	return it != table.end() ? it->second : table.at(EffectType::Pop);
}
