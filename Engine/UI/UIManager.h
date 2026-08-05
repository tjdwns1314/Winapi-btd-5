#pragma once
#include "Singleton.h"
#include "Widget.h"

class UIManager : public Singleton<UIManager>
{
	friend Singleton<UIManager>;

public:
	void Register(Widget* widget);
	void Clear();
	void Update(float deltaTime);

private :
	UIManager() = default;
	~UIManager() = default;

	vector<Widget*> _widgets;

};
