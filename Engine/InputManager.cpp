#include "pch.h"
#include "InputManager.h"

void InputManager::Update()
{
	for (int32 i = 0; i < 2; ++i)
		_prevPressed[i] = _currPressed[i];

	_currPressed[static_cast<int32>(KeyType::LeftMouse)] = (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	_currPressed[static_cast<int32>(KeyType::RightMouse)] = (::GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;

	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(_hwnd, &pt);
	_mousePos = Vector(static_cast<float>(pt.x), static_cast<float>(pt.y));
}

bool InputManager::GetButtonDown(KeyType key) const
{
	const int32 index = static_cast<int32>(key);
	return _currPressed[index] && !_prevPressed[index]; // 눌리는 그 순간(edge)만 true
}
