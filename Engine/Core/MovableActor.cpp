#include "pch.h"
#include "MovableActor.h"
#include "Collider.h"

MovableActor::~MovableActor()
{
	delete _collider;
}

void MovableActor::Update(float deltaTime)
{
	Super::Update(deltaTime);
}

void MovableActor::Render(Graphic& graphic)
{
	Super::Render(graphic);
}

void MovableActor::Move(float deltaTime)
{
	// 프레임률과 무관하게 같은 속도로 움직이도록 deltaTime을 곱한다.
	SetPos(GetPos() + _dir * (_moveSpeed * deltaTime));
}
void MovableActor::Init()
{
	Super::Init();
}

void MovableActor::SetCollider(Collider* collider)
{
	delete _collider;
	_collider = collider;
}
