#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Bloon.h"
#include "ColliderCircle.h"
#include "PoolManager.h"
#include "Effect.h"
#include "EffectFactory.h"
#include "AudioManager.h"

namespace
{
	constexpr float kProjectileBaseScale = 0.7f;
}

void Projectile::Init()
{
	Super::Init();
	SetActorType(ActorType::Projectile);
	SetLayer(RenderLayer::Projectile);
	ResourceManager& res = ResourceManager::GetInstance();
	_image = &res.GetImage(L"Resource\\Sprite\\InGame.png");

	_cell = res.GetAtlas(L"Resource\\Sprite\\InGame.xml").GetCell(_spriteKey);

	SetScale(Vector(kProjectileBaseScale, kProjectileBaseScale));

	_traveledDistance = 0.f;	// 풀에서 재사용될 때 이전 비행 거리가 남지 않도록 초기화
	_pierceRemaining = _pierceCount;
	SetMoveSpeed(_speed);
	SetCollider(new ColliderCircle(this, 20.f * kProjectileBaseScale));
	const Vector dir = GetDir();
	SetRotation(RadianToDegree(atan2f(dir.x, -dir.y)));
}

void Projectile::Update(float deltaTime)
{
	Super::Update(deltaTime);
	const float step = GetMoveSpeed() * deltaTime;
	Move(deltaTime);
	_traveledDistance += step;
	if (_traveledDistance >= _maxDistance)
		SetPendingKill();
}

void Projectile::OnEnter(Actor* other)
{
	if (other == nullptr || other->GetActorType() != ActorType::Bloon)
		return;

	if (_splashRadius > 0.f)
	{
		const Vector center = GetPos();
		const vector<Actor*> bloons = GetOwner()->GetActors(RenderLayer::Bloon);
		for (Actor* actor : bloons)
		{
			if (actor == other || actor->IsPendingKill())
				continue;
			if ((actor->GetPos() - center).Length() <= _splashRadius)
				static_cast<Bloon*>(actor)->ApplyDamage(_damage);
		}

		Effect* explosion = EffectFactory::Create(PoolManager::GetInstance().GetEffectPool(), center, EffectType::Explosion);
		if (explosion != nullptr)
			GetOwner()->AddActor(explosion);

		AudioManager::GetInstance().PlaySfx(L"explosion_small");
	}
	if (--_pierceRemaining <= 0)
		SetPendingKill();
}

void Projectile::Render(Graphic& graphic)
{
	Super::Render(graphic);
	if (_image == nullptr || _cell == nullptr)
		return;
		
	const Vector pos = GetPos();
	const Vector scale = GetScale();
	_image->DrawSprite(graphic, pos.x, pos.y,*_cell, scale.x,GetRotation());

}
