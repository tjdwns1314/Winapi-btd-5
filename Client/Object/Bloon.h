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
	virtual void OnEnter(Actor* other) override;

	BloonColor GetColor() const { return _color; }
	void SetColor(BloonColor color) { _color = color; }
	void SetPath(const vector<Vector>* path, size_t waypointIndex = 0) { _path = path; _waypointIndex = waypointIndex; }
	size_t GetWaypointIndex() const { return _waypointIndex; }

	void SetHp(int32 hp) { _hp = hp; }
	void SetImage(Image* image) { _image = image; }

private:
	//static const wchar_t* getImageKey(BloonColor color);
	void followPath(float deltaTime);
	void spawnNextTier() const;

	// 등급 체인은 BloonType.h의 BloonColor(Red~Ceramic)를 기준으로 삼는다.
	BloonColor _color = BloonColor::Red;
	int32 _hp = 1;
	Image* _image = nullptr;

	const vector<Vector>* _path = nullptr;
	size_t _waypointIndex = 0;
};

