#include "pch.h"
#include "UIManager.h"

void UIManager::Register(Widget* widget)
{
	if (widget != nullptr)
		_widgets.push_back(widget);
}

void UIManager::Clear()
{
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
