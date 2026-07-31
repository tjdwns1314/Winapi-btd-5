#pragma once
#include "Actor.h"
class MovableActor : public Actor
{
	using Super = Actor;
public:
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	virtual void Move(float deltaTime);

	Vector GetDir() const { return _dir; }
	void SetDir(const Vector& dir) { _dir = dir;}
	float GetMoveSpeed() const { return _moveSpeed;}
	void SetMoveSpeed(float speed) { _moveSpeed = speed; }

protected:
	Vector _dir;
	float _moveSpeed;
};

