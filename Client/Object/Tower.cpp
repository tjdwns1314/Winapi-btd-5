#include "pch.h"
#include "Tower.h"
#include "GameScene.h"
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
	_fireTimer = _stat.attackSpeed;	// 처음 타겟이 잡히면 쿨타임 대기 없이 바로 쏘도록 미리 채워둔다.
}

void Tower::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 타겟이 죽었거나 사거리를 벗어났으면 놓아준다.
	if (_target != nullptr && (_target->IsPendingKill() || isInRange(_target) == false))
		_target = nullptr;

	if (_target == nullptr)
		_target = findTarget();

	if (_stat.rotatesToTarget && _target != nullptr)
	{
		Vector dir = _target->GetPos() - GetPos();
		if (dir.Length() >= SMALL_NUMBER)
			SetRotation(RadianToDegree(atan2f(dir.x, -dir.y)));
	}

	// 타겟 유무와 상관없이 쿨타임은 계속 흐른다. 발사 자체만 타겟이 있을 때로 제한한다.
	_fireTimer += deltaTime;
	if (_target == nullptr || _fireTimer < _stat.attackSpeed)
		return;

	_fireTimer = 0.f;
	fire();
}

void Tower::Render(Graphic& graphic)
{
	Super::Render(graphic);
	const Vector pos = GetPos();
	const Vector scale = GetScale();

	if (_bakedImage != nullptr)
		_bakedImage->Draw(graphic, pos.x, pos.y, scale.x, GetRotation());
	else if (_image != nullptr && _cell != nullptr)
		_image->DrawSprite(graphic, pos.x, pos.y, *_cell, scale.x, GetRotation());
	else
		return;

	RenderRange(graphic);
}

void Tower::RenderRange(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::White, 0.5f));
	if (renderTarget == nullptr || brush == nullptr)
		return;
	const Vector pos = GetPos();
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(pos.x, pos.y), _stat.attackRange, _stat.attackRange), brush, 2.f);
}

bool Tower::isInRange(const Actor* target) const
{
	if (target == nullptr)
		return false;

	const float range = _stat.attackRange + GetColliderRadius(target);
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

int32 Tower::GetNextUpgradeCost() const
{
	if (!_canUpgrade)
		return 0;

	const int32 upgradeIndex = _grade - 1;
	if (upgradeIndex < 0 || upgradeIndex >= static_cast<int32>(_stat.upgradeCosts.size()))
		return 0;
	return _stat.upgradeCosts[upgradeIndex];
}

void Tower::ApplyUpgrade()
{
	if (!_canUpgrade)
		return;
	++_grade;
	_canUpgrade = (_grade - 1) < static_cast<int32>(_stat.upgradeCosts.size());
}

GameScene* Tower::GetGameScene() const
{
	return static_cast<GameScene*>(GetOwner());
}

void Tower::fire()
{
	if (_fireBehavior != nullptr)
		_fireBehavior(*this);
}
