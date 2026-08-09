#include "pch.h"
#include "Tower.h"
#include "GameScene.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "ColliderCircle.h"

namespace
{
	float GetColliderRadius(const Actor* actor)
	{
		if (actor == nullptr)
			return 0.f;
		Collider* collider = actor->GetCollider();
		if (collider == nullptr || collider->GetType() != ColliderType::Circle)
			return 0.f;

		return static_cast<ColliderCircle*>(collider)->GetRadius();
	}
}



void Tower::Init()
{
	Super::Init();
	SetActorType(ActorType::Tower);
	SetLayer(RenderLayer::Tower);

	ResourceManager& res = ResourceManager::GetInstance();
	_image = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_cell = res.GetAtlas(L"Resource\\Sprite\\InGame.xml").GetCell(GetSpriteName());
}

void Tower::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 타겟이 죽었거나 사거리를 벗어났으면 놓아준다.
	if (_target != nullptr && (_target->IsPendingKill() || isInRange(_target) == false))
		_target = nullptr;

	if (_target == nullptr)
		_target = findTarget();

	if (_target != nullptr)
	{
		Vector dir = _target->GetPos() - GetPos();
		if (dir.Length() >= SMALL_NUMBER)
			SetRotation(RadianToDegree(atan2f(dir.x, -dir.y)));
	}

	_fireTimer += deltaTime;
	if (_fireTimer >= _attackSpeed)
	{
		_fireTimer -= _attackSpeed;
		fire();
	}
}

void Tower::Render(Graphic& graphic)
{
	Super::Render(graphic);
	if (_image == nullptr || _cell == nullptr)
		return;
	const Vector pos = GetPos();
	const Vector scale = GetScale();
	_image->DrawSprite(graphic, pos.x, pos.y, *_cell, scale.x, GetRotation());
	RenderRange(graphic);
}

void Tower::RenderRange(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::White, 0.5f));
	if (renderTarget == nullptr || brush == nullptr)
		return;
	const Vector pos = GetPos();
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), _attackRange, _attackRange), brush, 2.f);

}

void Tower::fire()
{
	if (_target == nullptr)
		return;

	GameScene* owner = static_cast<GameScene*>(GetOwner());
	if (owner == nullptr)
		return;


	Vector dir = _target->GetPos() - GetPos();
	if (dir.Length() < SMALL_NUMBER)
		return;

	dir.Normalize();
	owner->SpawnProjectile(GetPos(), dir, _damage);
}

const char* Tower::GetSpriteName()
{
	return "dart_monkey_body";
}

bool Tower::isInRange(const Actor* target) const
{
	if (target == nullptr)
		return false;

	const float range = _attackRange + GetColliderRadius(target);
	const Vector diff = target->GetPos() - GetPos();
	const float distSq = diff.x * diff.x + diff.y * diff.y;
	return distSq <= range * range;
}

Bloon* Tower::findTarget() const
{
	// Tower는 GameScene에서만 생성되므로 안전하게 다운캐스팅한다.
	GameScene* owner = static_cast<GameScene*>(GetOwner());
	if (owner == nullptr)
		return nullptr;

	Bloon* nearest = nullptr;
	float nearestDistSq = FLT_MAX;

	for (Actor* actor : owner->GetActors(RenderLayer::Bloon))
	{
		if (actor->IsPendingKill())
			continue;

		const Vector diff = actor->GetPos() - GetPos();
		const float distSq = diff.x * diff.x + diff.y * diff.y;
		if (nearest != nullptr && distSq >= nearestDistSq)
			continue;
		if (isInRange(actor) == false)
			continue;
		nearest = static_cast<Bloon*>(actor);
		nearestDistSq = distSq;
	}
	return nearest;
}
