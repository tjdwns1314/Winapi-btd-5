#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "ColliderCircle.h"

void Projectile::Init()
{
	Super::Init();
	SetActorType(ActorType::Projectile);
	SetLayer(RenderLayer::Projectile);
	ResourceManager& res = ResourceManager::GetInstance();
	_image = &res.GetImage(L"Resource\\Sprite\\InGame.png");
	_cell = res.GetAtlas(L"Resource\\Sprite\\InGame.xml").GetCell(GetSpriteName());
	_traveledDistance = 0.f;	// 풀에서 재사용될 때 이전 비행 거리가 남지 않도록 초기화
	SetMoveSpeed(500.f);	// 투사체 속도 (placeholder: 눈으로 확인 가능한 값, 실제 밸런스는 추후 조정)
	SetCollider(new ColliderCircle(this, 20.f));
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
	if (other != nullptr && other->GetActorType() == ActorType::Bloon)
		SetPendingKill();
}

void Projectile::Render(Graphic& graphic)
{
	Super::Render(graphic);
	if (_image == nullptr || _cell == nullptr)
		return;
		
	const Vector pos = GetPos();
	const Vector scale = GetScale();
	_image->DrawSprite(graphic, pos.x, pos.y,*_cell, scale.x);

}
const char* Projectile::GetSpriteName()
{
	return "dart_monkey_dart";
}
