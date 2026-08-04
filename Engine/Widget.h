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

private:
	Vector _pos;
	Vector _size;
	bool _active = true;
};
