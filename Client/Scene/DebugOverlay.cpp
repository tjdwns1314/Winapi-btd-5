#include "pch.h"
#include "DebugOverlay.h"
#include "Graphic.h"
#include "MapSystem.h"
#include "Actor.h"
#include "Collider.h"

void DebugOverlay::AddCircle(const Vector& pos, float radius, float duration)
{
	_circles.push_back({ pos, radius, duration });
}

void DebugOverlay::Update(float deltaTime)
{
	for (DebugCircle& circle : _circles)
		circle.remaining -= deltaTime;

	std::erase_if(_circles, [](const DebugCircle& circle)
		{
			return circle.remaining <= 0.f;
		});
}

void DebugOverlay::Render(Graphic& graphic, const MapSystem& map, bool isDragging, const vector<Actor*>& bloons,
	bool isSpecialWaveActive) const
{
	map.RenderPathDebug(graphic);
	if (isSpecialWaveActive)
		map.RenderRiskPathDebug(graphic);

	if (_enabled)
	{
		map.RenderGrid(graphic, D2D1::ColorF(D2D1::ColorF::Black, 0.8f));
		renderColliders(graphic, bloons);
	}
	else if (isDragging)
	{
		map.RenderGrid(graphic, D2D1::ColorF(D2D1::ColorF::Black, 0.8f));
	}
	renderCircles(graphic);
}

void DebugOverlay::renderColliders(Graphic& graphic, const vector<Actor*>& bloons) const
{
	for (Actor* actor : bloons)
	{
		Collider* collider = actor->GetCollider();
		if (collider != nullptr)
			collider->Render(graphic);
	}
}

void DebugOverlay::renderCircles(Graphic& graphic) const
{
	ID2D1HwndRenderTarget* renderTarget = graphic.GetRenderTarget();
	ID2D1SolidColorBrush* brush = graphic.GetBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 0.6f));
	if (renderTarget == nullptr || brush == nullptr)
		return;

	for (const DebugCircle& circle : _circles)
		renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(circle.pos.x, circle.pos.y), circle.radius, circle.radius), brush, 2.f);
}
