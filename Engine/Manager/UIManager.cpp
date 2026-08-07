#include "pch.h"
#include "UIManager.h"

UIManager::~UIManager()
{
	Clear();
}

void UIManager::Register(Widget* widget)
{
	if (widget != nullptr)
		_widgets.push_back(widget);
}

void UIManager::Clear()
{
	for (Widget* widget : _widgets)
		delete widget;

	_widgets.clear();
}

void UIManager::Update(float deltaTime)
{
	for (Widget* widget : _widgets)
	{
		if (widget->IsActive())
			widget->Update(deltaTime);
	}
}

void UIManager::Render(Graphic& graphic)
{
	for (Widget* widget : _widgets)
	{
		if (widget->IsActive())
			widget->Render(graphic);
	}
}
