#pragma once
#include "Singleton.h"

enum class KeyType
{
	LeftMouse,
	RightMouse,
	F1,
	F2,
	Escape,
	Space,
};

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;

public:
	void Init(HWND hwnd) { _hwnd = hwnd; }
	void Update();

	bool GetButtonDown(KeyType key) const;
	bool GetButtonUp(KeyType key) const;
	Vector GetMousePos() const { return _mousePos; }

private:
	InputManager() = default;
	~InputManager() = default;

	HWND _hwnd = nullptr;
	Vector _mousePos;
	bool _prevPressed[6] = {};
	bool _currPressed[6] = {};
};
