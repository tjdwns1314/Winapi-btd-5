#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"

void Projectile::Init()
{
	Super::Init();
	SetActorType(ActorType::Projectile);
	SetLayer(static_cast<int32>(RenderLayer::Projectile));
	_image = &ResourceManager::GetInstance().GetImage(getImageKey());
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
	if (_image == nullptr)
		return;
	const Vector pos = GetPos();
	const Vector scale = GetScale();
	_image->Draw(graphic, pos.x, pos.y, scale.x);

}
const wchar_t* Projectile::getImageKey()
{
	return L"Resource\\projectileImg.png";
}
