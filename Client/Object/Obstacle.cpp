#include "pch.h"
#include "Obstacle.h"
#include "Image.h"

void Obstacle::Init()
{
	Super::Init();
	SetActorType(ActorType::Block); // 기존 ActorType 중 정적 장애물에 해당하는 값 재사용
	SetLayer(RenderLayer::Obstacle);
}

void Obstacle::Render(Graphic& graphic)
{
	Super::Render(graphic);
	if (_image == nullptr || _cell == nullptr)
		return;

	const Vector pos = GetPos();
	const Vector scale = GetScale();
	_image->DrawSprite(graphic, pos.x, pos.y, *_cell, scale.x, GetRotation());
}
