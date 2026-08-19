#include "pch.h"
#include "Widget.h"

Widget::~Widget()
{
}

void Widget::Init()
{
}

void Widget::Update(float deltaTime)
{
}

void Widget::Render(Graphic& graphic)
{
}

bool Widget::ContainsPoint(const Vector& point) const
{
	const float left = _pos.x - _size.x * 0.5f;
	const float right = _pos.x + _size.x * 0.5f;
	const float top = _pos.y - _size.y * 0.5f;
	const float bottom = _pos.y + _size.y * 0.5f;
	return point.x >= left && point.x <= right && point.y >= top && point.y <= bottom;
}
