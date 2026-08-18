#include "pch.h"
#include "InputManager.h"

void InputManager::Update()
{
	for (int32 i = 0; i < static_cast<int32>(std::size(_prevPressed)); ++i)
		_prevPressed[i] = _currPressed[i];

	_currPressed[static_cast<int32>(KeyType::LeftMouse)] = (::GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
	_currPressed[static_cast<int32>(KeyType::RightMouse)] = (::GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
	_currPressed[static_cast<int32>(KeyType::F1)] = (::GetAsyncKeyState(VK_F1) & 0x8000) != 0;
	_currPressed[static_cast<int32>(KeyType::F2)] = (::GetAsyncKeyState(VK_F2) & 0x8000) != 0;
	_currPressed[static_cast<int32>(KeyType::Escape)] = (::GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0;
	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(_hwnd, &pt);

	RECT rc;
	::GetClientRect(_hwnd, &rc);
	const float cw = static_cast<float>(rc.right - rc.left);
	const float ch = static_cast<float>(rc.bottom - rc.top);
	if (cw > 0.f && ch > 0.f)
	{
		const float sx = cw / static_cast<float>(GWinSizeX);
		const float sy = ch / static_cast<float>(GWinSizeY);
		const float scale = (sx < sy) ? sx : sy;
		const float offsetX = (cw - static_cast<float>(GWinSizeX) * scale) * 0.5f;
		const float offsetY = (ch - static_cast<float>(GWinSizeY) * scale) * 0.5f;
		_mousePos = Vector((pt.x - offsetX) / scale, (pt.y - offsetY) / scale);
	}
	else
		_mousePos = Vector(static_cast<float>(pt.x), static_cast<float>(pt.y));
}

bool InputManager::GetButtonDown(KeyType key) const
{
	const int32 index = static_cast<int32>(key);
	return _currPressed[index] && !_prevPressed[index]; // 눌리는 그 순간(edge)만 true
}

bool InputManager::GetButtonUp(KeyType key) const
{
	const int32 index = static_cast<int32>(key);
	return !_currPressed[index] && _prevPressed[index]; // 떼는 그 순간(edge)만 true
}
