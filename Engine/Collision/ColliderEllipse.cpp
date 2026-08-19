#include "pch.h"
#include "ColliderEllipse.h"
#include "ColliderCircle.h"
#include "Actor.h"
#include "Graphic.h"

// 정밀한 타원-타원 교차식 대신, 두 도형의 반지름 합으로 좌표를 정규화해
// "정규화된 거리 < 1"인지로 판정하는 근사식을 쓴다. (미검증: 곡률 차이가 큰 조합에서 오차 가능)
bool ColliderEllipse::CheckCollision(Collider* other)
{
	if (nullptr == other)
		return false;

	Vector diff = GetOwner()->GetPos() - other->GetOwner()->GetPos();

	switch (other->GetType())
	{
	case ColliderType::Circle:
	{
		ColliderCircle* circle = static_cast<ColliderCircle*>(other);
		float nx = diff.x / (_radiusX + circle->GetRadius());
		float ny = diff.y / (_radiusY + circle->GetRadius());
		return (nx * nx + ny * ny) < 1.f;
	}
	case ColliderType::Ellipse:
	{
		ColliderEllipse* ellipse = static_cast<ColliderEllipse*>(other);
		float nx = diff.x / (_radiusX + ellipse->_radiusX);
		float ny = diff.y / (_radiusY + ellipse->_radiusY);
		return (nx * nx + ny * ny) < 1.f;
	}
	default:
		return false;
	}
}

void ColliderEllipse::Render(Graphic& graphic)
{
	Vector pos = GetOwner()->GetPos();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Red, 0.6f));
	graphic.GetRenderTarget()->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), _radiusX, _radiusY), brush, 2.f);
}
