#include "pch.h"
#include "Bloon.h"
#include "ColliderCircle.h"
#include "Projectile.h"


void Bloon::Init()
{
	Super::Init();
	SetActorType(ActorType::Bloon);
	if (_image == nullptr)
		return;
	const D2D1_SIZE_F size = _image->GetSize();
	const float scale = static_cast<float>(BLOCK_SIZE) / size.width;
	SetScale(Vector(scale, scale));
	SetCollider(new ColliderCircle(this, static_cast<float>(BLOCK_SIZE) / 2.f));
	SetLayer(RenderLayer::Bloon);
}

void Bloon::OnEnter(Actor* other)
{
	if (other == nullptr || other->GetActorType() != ActorType::Projectile)
	{
		return;
	}

	if (!_hitHandler)
		return;

	const Projectile* projectile = static_cast<Projectile*>(other);
	_hitHandler(*this, projectile->GetDamage());
}

void Bloon::Update(float deltaTime)
{
	Super::Update(deltaTime);
	followPath(deltaTime);
}

void Bloon::Render(Graphic& graphic)
{
	Super::Render(graphic);

	if (_image == nullptr)
		return;

	const Vector pos = GetPos();
	const Vector scale = GetScale();
	_image->Draw(graphic, pos.x, pos.y, scale.x);
}

//const wchar_t* Bloon::getImageKey(BloonColor color)
//{
//	// TODO: 색상별 스프라이트가 추가되면 여기서 분기한다. 현재는 공용 이미지 하나만 존재.
//	return L"Resource\\Sprite\\bloonImg.png";
//}

void Bloon::followPath(float deltaTime)
{
	if (_path == nullptr || _waypointIndex >= _path->size())
		return;

	Vector target = (*_path)[_waypointIndex];
	const Vector toTarget = target - GetPos();
	const float distSq = toTarget.x * toTarget.x + toTarget.y * toTarget.y;
	const float step = GetMoveSpeed() * deltaTime;

	if (distSq <= step * step)
	{
		SetPos(target);
		++_waypointIndex;
		if (_waypointIndex >= _path->size())
		{
			if (_leakHandler)
				_leakHandler(*this);
			SetPendingKill();
		}
		return;
	}

	const float dist = std::sqrtf(distSq);
	SetDir(Vector(toTarget.x / dist, toTarget.y / dist));
	Move(deltaTime); // MovableActor::Move가 _dir * _moveSpeed * deltaTime 만큼 이동시킴
}

