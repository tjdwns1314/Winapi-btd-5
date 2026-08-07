#pragma once
#include "Collider.h"

// 타원형 충돌체. 보스 풍선처럼 진행 방향으로 길쭉한 모양이 필요할 때 사용한다.
class ColliderEllipse : public Collider
{
public:
	ColliderEllipse(Actor* owner, float radiusX, float radiusY) : Collider(owner, ColliderType::Ellipse), _radiusX(radiusX), _radiusY(radiusY) {}

	virtual bool CheckCollision(Collider* other) override;
	virtual void Render(Graphic& graphic) override;

	float GetRadiusX() const { return _radiusX; }
	float GetRadiusY() const { return _radiusY; }

private:
	float _radiusX = 0.f;
	float _radiusY = 0.f;
};
