#pragma once

class Graphic;

class Widget
{
public:
	virtual ~Widget();

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(Graphic& graphic);

	Vector GetPos() const { return _pos; }
	void SetPos(const Vector& pos) { _pos = pos; }

	Vector GetSize() const { return _size; }
	void SetSize(const Vector& size) { _size = size; }

	bool ContainsPoint(const Vector& point) const;

	bool IsActive() const { return _active; }
	void SetActive(bool active) { _active = active; }

	// true면 UIManager가 입력을 잠갔을 때도(모달 팝업이 떠 있어도) 이 위젯은 클릭이 계속 먹힌다.
	// Render(그리기) 여부는 여전히 _active만 따르므로, 다른 위젯을 숨기지 않고 클릭만 막을 때 쓴다.
	bool IgnoresModalLock() const { return _ignoresModalLock; }
	void SetIgnoresModalLock(bool ignoresModalLock) { _ignoresModalLock = ignoresModalLock; }

private:
	Vector _pos;
	Vector _size;
	bool _active = true;
	bool _ignoresModalLock = false;
};
