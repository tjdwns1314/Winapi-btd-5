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
	virtual void OnEnter(Actor* other) override;

	RenderLayer GetRenderLayer() const { return RenderLayer::Projectile; }

	void SetDamage(float damage) { _damage = damage; }
	float GetDamage() const { return _damage; }

	void SetSpriteKey(const string& key) { _spriteKey = key; }

	void SetProjectileSpeed(float speed) { _speed = speed; }
	void SetSplashRadius(float radius) { _splashRadius = radius; }

private:
	float _damage = 1.f;
	float _maxDistance = 800.f;	// 이 거리 이상 날아가면 삭제 (placeholder, 실제 사거리 확인 후 조정)
	float _traveledDistance = 0.f;
	float _speed = 500.0f;
	float _splashRadius = 0.f;

	Image* _image = nullptr;

	const CellInfo* _cell = nullptr;
	string _spriteKey = "dart_monkey_dart";
};

