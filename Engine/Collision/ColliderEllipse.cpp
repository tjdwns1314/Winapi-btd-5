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
	// 소유자의 회전(이동 방향)만큼 반대로 되돌려 타원의 로컬 좌표계로 변환한다.
	diff = diff.Rotate(-DegreeToRadian(GetOwner()->GetRotation()));

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

	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	D2D1::Matrix3x2F prev;
	renderTarget->GetTransform(&prev);
	// Image::Draw와 동일한 방식으로 소유자 회전만큼 디버그 타원도 같이 돌려 그린다.
	renderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(GetOwner()->GetRotation(), D2D1::Point2F(pos.x, pos.y)) * prev);
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), _radiusX, _radiusY), brush, 2.f);
	renderTarget->SetTransform(prev);
}
