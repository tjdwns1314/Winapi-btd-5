#include "pch.h"
#include "ColliderCircle.h"
#include "Actor.h"
#include "Graphic.h"


bool ColliderCircle::CheckCollision(Collider* other)
{
    if (nullptr == other)
        return false;

    switch (other->GetType())
    {
    case ColliderType::Circle:
    {
        ColliderCircle* circle = static_cast<ColliderCircle*>(other);
        Vector diff = GetOwner()->GetPos() - circle->GetOwner()->GetPos();
        return diff.Length() < _radius + circle->GetRadius();
    }
    case ColliderType::Ellipse:
        return other->CheckCollision(this);
    default :
        return false;
    }
}

void ColliderCircle::Render(Graphic& graphic)
{
    Vector pos = GetOwner()->GetPos();
    ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Red, 0.6f));
    graphic.GetRenderTarget()->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), _radius, _radius), brush, 2.f);
}
