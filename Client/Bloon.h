#pragma once
#include "MovableActor.h"

enum class BloonType{Red,Blue,Green,Yellow,Pink};

class Bloon : public MovableActor
{
	using Super = MovableActor;

public :
	virtual void Update(float deltaTime) override;
	virtual void Render(HDC hdc) override;

	/*void TakeDamage(int damage);
	bool IsPopped() const { return _isPopped; }*/



private:
	BloonType _type;
	int _hp;
};

