#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"

void Projectile::Init()
{
	Super::Init();
	SetActorType(ActorType::Projectile);
	SetLayer(RenderLayer::Projectile);
	ResourceManager& res = ResourceManager::GetInstance();
	_image = &res.GetImage(L"Resource\\InGame.png");
	_cell = res.GetAtlas(L"Resource\\InGame.xml").GetCell(GetSpriteName());
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
