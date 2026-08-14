#include "pch.h"
#include "Tower.h"
#include "GameScene.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include "ResourceManager.h"

namespace
{
	constexpr float kThrowFrameDuration = 0.08f; // 프레임당 재생 시간(초). 시각 확인 후 조정 필요(미검증)
	constexpr int32 kThrowFrameCount = 3;

	// 손(투사체 발사 지점)의 로컬 오프셋. 캔버스({125,140}) 중심 기준, 프레임(arm_01~03)별.
	// TODO(미검증): 실제 스프라이트를 보고 값 조정 필요. 지금은 placeholder로 baseline offset을 그대로 씀.
	const Vector kDartHandLocalOffset[kThrowFrameCount] =
	{
		{ 2.0f, 0.0f },
		{ 2.0f, 0.0f },
		{ 2.0f, 0.0f },
	};

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
	_target = nullptr;
	_grade = 1;
	_canUpgrade = true;
	_isThrowing = false;
	_animFrame = 0;
	_animTimer = 0.f;
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

	if (_towerData->rotatesToTarget && _target != nullptr)
	{
		Vector dir = _target->GetPos() - GetPos();
		if (dir.Length() >= SMALL_NUMBER)
			SetRotation(RadianToDegree(atan2f(dir.x, -dir.y)));
	}

	if (_isThrowing)
	{
		updateThrowAnimation(deltaTime);
		return; // 던지는 도중에는 쿨타임을 새로 세지 않는다.
	}

	// 타겟 유무와 상관없이 쿨타임은 계속 흐른다. 발사 자체만 타겟이 있을 때로 제한한다.
	_fireTimer += deltaTime;
	if (_target == nullptr || _fireTimer < _stat.attackSpeed)
		return;

	_fireTimer = 0.f;

	if (_frameKeyFn != nullptr)
	{
		_isThrowing = true;
		_animFrame = 0;
		_animTimer = 0.f;
	}
	else
	{
		fire();
	}
}

void Tower::updateThrowAnimation(float deltaTime)
{
	_animTimer += deltaTime;
	if (_animTimer < kThrowFrameDuration)
		return;

	_animTimer = 0.f;
	++_animFrame;

	if (_animFrame < kThrowFrameCount)
		return; // 다음 프레임으로 넘어감

	// 마지막 프레임까지 재생이 끝난 시점에 실제로 투사체를 발사한다.
	fire();
	_isThrowing = false;
	_animFrame = 0;
}

void Tower::Render(Graphic& graphic)
{
	Super::Render(graphic);
	const Vector pos = GetPos();
	const Vector scale = GetScale();

	if (_frameKeyFn != nullptr)
	{
		wchar_t key[128];
		_frameKeyFn(_grade, _animFrame, key, std::size(key));
		ResourceManager::GetInstance().GetImage(key).Draw(graphic, pos.x, pos.y, scale.x, GetRotation());
	}
	else if (_bakedImage != nullptr)
		_bakedImage->Draw(graphic, pos.x, pos.y, scale.x, GetRotation());
	else if (_image != nullptr && _cell != nullptr)
		_image->DrawSprite(graphic, pos.x, pos.y, *_cell, scale.x, GetRotation());
	else
		return;

	RenderRange(graphic);
}

Vector Tower::getHandLocalOffset() const
{
	const int32 frame = std::clamp(_animFrame, 0, kThrowFrameCount - 1);
	return kDartHandLocalOffset[frame];
}

Vector Tower::GetFirePos() const
{
	if (_frameKeyFn == nullptr)
		return GetPos();

	return GetPos() + getHandLocalOffset().Rotate(DegreeToRadian(GetRotation())) * GetScale().x;
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

	const int32 targetIndex = _grade;  
	if (targetIndex < 0 || targetIndex >= static_cast<int32>(_towerData->grades.size()))
		return 0;
	return _towerData->grades[targetIndex].cost;
}

void Tower::ApplyUpgrade()
{
	if (!_canUpgrade)
		return;
	const int32 targetIndex = _grade;
	if (targetIndex < 0 || targetIndex >= static_cast<int32>(_towerData->grades.size()))
		return;
	_stat = _towerData->grades[targetIndex];
	++_grade;
	_canUpgrade = _grade < static_cast<int32>(_towerData->grades.size());
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
