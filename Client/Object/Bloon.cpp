#include "pch.h"
#include "Bloon.h"
#include "ResourceManager.h"

void Bloon::Init()
{
	Super::Init();
	SetActorType(ActorType::Bloon);
	_image = &ResourceManager::GetInstance().GetImage(getImageKey(_color));

	const D2D1_SIZE_F size = _image->GetSize();
	const float scale = static_cast<float>(BLOCK_SIZE) / size.width;
	SetScale(Vector(scale, scale));

	// TODO: 색상별 이동속도 데이터가 생기면 여기서 분기한다.
	SetMoveSpeed(300.f);
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
