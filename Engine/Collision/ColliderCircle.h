#pragma once
#include "Collider.h"

class ColliderCircle : public Collider
{
public:
	ColliderCircle(Actor* owner, float radius) : Collider(owner, ColliderType::Circle), _radius(radius) {}

	virtual bool CheckCollision(Collider* other) override;
	virtual void Render(Graphic& graphic) override;

	float GetRadius() const { return _radius; }


private:
	float _radius = 0.f;

};