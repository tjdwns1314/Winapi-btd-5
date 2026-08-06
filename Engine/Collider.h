#pragma once
#include"Util.h"
class Actor;
class Graphic;

class Collider
{
public:
	Collider(Actor* owner, ColliderType type) : _owner(owner), _type(type) {}
	virtual ~Collider() = default;

	virtual bool CheckCollision(Collider* other) = 0;
	virtual void Render(Graphic& graphic) = 0;

	Actor* GetOwner() const { return _owner; }
	ColliderType GetType() const { return _type; }

protected:
	Actor* _owner = nullptr;
	ColliderType _type = ColliderType::Max;
};

