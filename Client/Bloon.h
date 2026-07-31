#pragma once
#include "MovableActor.h"
#include "BloonType.h"

class Bloon : public MovableActor
{
	using Super = MovableActor;

public :
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;

	/*void TakeDamage(int damage);
	bool IsPopped() const { return _isPopped; }*/

	BloonColor GetColor() const { return _color; }

private:
	// 등급 체인은 BloonType.h의 BloonColor(Red~Ceramic)를 기준으로 삼는다.
	BloonColor _color = BloonColor::Red;
	int32 _hp = 1;
};

