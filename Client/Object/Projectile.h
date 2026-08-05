#pragma once
#include "MovableActor.h"

class Image;
struct CellInfo;

class Projectile : public MovableActor
{
	using Super = MovableActor;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;

	RenderLayer GetRenderLayer() const { return RenderLayer::Projectile; }

	void SetDamage(float damage) { _damage = damage; }
	float GetDamage() const { return _damage; }

private:
	static const char* GetSpriteName();

	float _damage = 1.f;
	float _maxDistance = 800.f;	// 이 거리 이상 날아가면 삭제 (placeholder, 실제 사거리 확인 후 조정)
	float _traveledDistance = 0.f;
	Image* _image = nullptr;

	const CellInfo* _cell = nullptr;

};

