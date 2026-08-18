#pragma once

#include "Actor.h"
#include "EffectType.h"

class Image;
struct CellInfo;

// pop, explosion 등 "위치에 잠깐 나타났다 사라지는" 스프라이트 이펙트의 공용 클래스.
// 실제 프레임 구성은 EffectType별로 EffectType.cpp의 데이터 테이블에서 가져온다.
class Effect : public Actor
{
	using Super = Actor;

public:
	void SetEffectType(EffectType type) { _type = type; }

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;

private:
	EffectType _type = EffectType::Pop;
	Image* _image = nullptr;
	vector<const CellInfo*> _frames;
	float _frameTime = 0.05f;
	float _elapsed = 0.f; // 풀에서 재사용될 때 Init에서 0으로 리셋
};
