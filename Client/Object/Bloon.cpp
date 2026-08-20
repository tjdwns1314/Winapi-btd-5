#include "pch.h"
#include "Bloon.h"
#include "ColliderCircle.h"
#include "ColliderEllipse.h"
#include "Projectile.h"


namespace
{
	constexpr float kBloonBaseScale = 0.7f;
}

void Bloon::Init()
{
	Super::Init();
	SetActorType(ActorType::Bloon);
	if (_image == nullptr)
		return;
	const D2D1_SIZE_F size = _image->GetSize();
	const BloonStat& stat = GetBloonStat(_color);
	const bool isBoss = (_color == BloonColor::Boss1 || _color == BloonColor::Boss2);
	// 아틀라스 셀을 쓰는 풍선(_cell != nullptr)은 셀 자체의 폭을, 그 외에는 이미지 원본 폭을 기준으로 정규화한다.
	// (_cell이 있을 때 _image는 InGame.png 시트 전체라 size.width를 그대로 쓰면 안 된다.)
	const float spriteWidth = (_cell != nullptr) ? _cell->w : size.width;

	// 일반 풍선: 기존처럼 폭 기준으로 BLOCK_SIZE에 자동 정규화.
	// 보스 풍선: 베이크된 원본 픽셀 크기가 크므로, 정규화 없이 spriteScale을 최종 배율로 그대로 사용.
	const float scale = isBoss
		? stat.spriteScale
		: static_cast<float>(BLOCK_SIZE) / spriteWidth * kBloonBaseScale;

	SetScale(Vector(scale, scale));

	if (isBoss)
	{
		// 판정 범위가 스프라이트 세로 길이에 딱 맞으면 다소 빡빡해 보여서, 진행 방향 축(radiusY)을 조금 더 늘린다.
		constexpr float kBossColliderLengthScale = 1.05f;
		// 보스는 세로로 긴 모양이므로 원 대신 타원 콜라이더로 실제 렌더된 폭/높이에 맞춘다.
		SetCollider(new ColliderEllipse(this, size.width * scale * 0.5f, size.height * scale * 0.5f * kBossColliderLengthScale));
	}
	else
	{
		SetCollider(new ColliderCircle(this, static_cast<float>(BLOCK_SIZE) / 2.f * kBloonBaseScale));
	}

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

	// 특수 풍선은 GameScene::Render가 타워 등 위에 별도로 그리므로 여기서는 건너뛴다.
	if (_color == BloonColor::Special)
		return;

	RenderSprite(graphic);
}

void Bloon::RenderSprite(Graphic& graphic)
{
	if (_image == nullptr)
		return;

	const Vector pos = GetPos();
	const Vector scale = GetScale();
	if (_cell != nullptr)
		_image->DrawSprite(graphic, pos.x, pos.y, *_cell, scale.x, GetRotation());
	else
		_image->Draw(graphic, pos.x, pos.y, scale.x, GetRotation());
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
	// 보스 풍선(MOAB/BFB)만 진행 방향을 바라보게 회전하고, 일반 풍선은 회전하지 않는다.
	const bool isBoss = (_color == BloonColor::Boss1 || _color == BloonColor::Boss2);
	if (isBoss)
		SetRotation(RadianToDegree(atan2f(toTarget.x, -toTarget.y))); // Projectile과 동일한 패턴: 이동 방향을 바라보게 회전

	Move(deltaTime); // MovableActor::Move가 _dir * _moveSpeed * deltaTime 만큼 이동시킴
}

