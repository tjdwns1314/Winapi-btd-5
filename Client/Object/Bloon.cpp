#include "pch.h"
#include "Bloon.h"
#include "ResourceManager.h"
#include "ColliderCircle.h"
#include "Projectile.h"
#include "GameScene.h"


void Bloon::Init()
{
	Super::Init();
	SetActorType(ActorType::Bloon);
	_image = &ResourceManager::GetInstance().GetImage(getImageKey(_color));

	const D2D1_SIZE_F size = _image->GetSize();
	const float scale = static_cast<float>(BLOCK_SIZE) / size.width;
	SetScale(Vector(scale, scale));
	SetCollider(new ColliderCircle(this, static_cast<float>(BLOCK_SIZE) / 2.f));

	// TODO: 색상별 이동속도 데이터가 생기면 여기서 분기한다.
	SetMoveSpeed(300.f);
	SetLayer(RenderLayer::Bloon);
}

void Bloon::OnEnter(Actor* other)
{
	if (other == nullptr || other->GetActorType() != ActorType::Projectile)
	{
		return;
	}

	const Projectile* projectile = static_cast<Projectile*>(other);
	_hp -= static_cast<int32>(projectile->GetDamage());
	if (_hp > 0)
		return;
	SetPendingKill();
	if (_color != BloonColor::Red)
		spawnNextTier();
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

const wchar_t* Bloon::getImageKey(BloonColor color)
{
	// TODO: 색상별 스프라이트가 추가되면 여기서 분기한다. 현재는 공용 이미지 하나만 존재.
	return L"Resource\\bloonImg.png";
}

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
			SetPendingKill();
		return;
	}

	const float dist = std::sqrtf(distSq);
	SetDir(Vector(toTarget.x / dist, toTarget.y / dist));
	Move(deltaTime); // MovableActor::Move가 _dir * _moveSpeed * deltaTime 만큼 이동시킴
}

void Bloon::spawnNextTier() const
{
	GameScene* owner = static_cast<GameScene*>
		(GetOwner());
	if (owner == nullptr)
		return;

	const BloonColor nextColor = static_cast<BloonColor>(static_cast<int32>(_color) - 1);
	owner->SpawnBloon(nextColor, GetPos(), _path);
}
