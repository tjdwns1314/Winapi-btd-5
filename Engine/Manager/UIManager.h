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

	// true면 IgnoresModalLock()이 false인 위젯은 Update(클릭 처리)만 건너뛴다. Render(그리기)는 영향받지 않는다.
	void SetInputLocked(bool locked) { _isInputLocked = locked; }

private :
	UIManager() = default;
	~UIManager();

	vector<Widget*> _widgets;
	bool _isInputLocked = false;

};
