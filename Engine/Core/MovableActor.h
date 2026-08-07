#pragma once
#include "Actor.h"

class Collider;

class MovableActor : public Actor
{
	using Super = Actor;
public:
	virtual ~MovableActor();

	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;
	virtual void Init() override;
	virtual void Move(float deltaTime);

	Vector GetDir() const { return _dir; }
	void SetDir(const Vector& dir) { _dir = dir;}
	float GetMoveSpeed() const { return _moveSpeed;}
	void SetMoveSpeed(float speed) { _moveSpeed = speed; }

	virtual Collider* GetCollider() const override { return _collider; }
	// 소유권을 넘겨받는다: 이전 콜라이더가 있으면 삭제하고 새 것으로 교체한다.
	void SetCollider(Collider* collider);

protected:
	Vector _dir;
	float _moveSpeed = 0.f;

private:
	Collider* _collider = nullptr;
};

