#pragma once

// 이펙트 종류. 추가될 때마다 여기 항목을 늘리고 EffectType.cpp의 GetEffectData 테이블을 채운다.
enum class EffectType
{
	Pop,
	Explosion,
};

struct EffectData
{
	vector<string> frameNames; // InGame.xml 셀 이름들. 순서대로 재생된다.
	float frameTime;           // 프레임당 재생 시간(초)
	float scale;
};

const EffectData& GetEffectData(EffectType type);
