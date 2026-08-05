#pragma once
#include "MovableActor.h"
#include "BloonType.h"
#include "Image.h"

class Bloon : public MovableActor
{
	using Super = MovableActor;

public :
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;

	BloonColor GetColor() const { return _color; }
	void SetColor(BloonColor color) { _color = color; }
	void SetPath(const vector<Vector>* path) { _path = path; _waypointIndex = 0; }

private:
	static const wchar_t* getImageKey(BloonColor color);
	void followPath(float deltaTime);

	// 등급 체인은 BloonType.h의 BloonColor(Red~Ceramic)를 기준으로 삼는다.
	BloonColor _color = BloonColor::Red;
	int32 _hp = 1;
	Image* _image = nullptr;

	const vector<Vector>* _path = nullptr;
	size_t _waypointIndex = 0;
};

