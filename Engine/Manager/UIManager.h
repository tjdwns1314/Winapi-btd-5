#pragma once
#include "Singleton.h"
#include "Widget.h"

class Graphic;
class UIManager : public Singleton<UIManager>
{
	friend Singleton<UIManager>;

public:
	void Register(Widget* widget);
	void Clear();
	void Update(float deltaTime);
	void Render(Graphic& graphic);

private :
	UIManager() = default;
	~UIManager();

	vector<Widget*> _widgets;

};
