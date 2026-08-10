#pragma once

#include "MovableActor.h"
#include "BloonType.h"
#include "Image.h"

class Bloon : public MovableActor
{
	using Super = MovableActor;

public:
	// 초기화 및 업데이트
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;
	virtual void OnEnter(Actor* other) override;

	// 풍선 정보
	BloonColor GetColor() const { return _color; }
	void SetColor(BloonColor color) { _color = color; }

	void SetHp(int32 hp) { _hp = hp; }
	void SetImage(Image* image) { _image = image; }

	// 경로 정보
	void SetPath(const vector<Vector>* path, size_t waypointIndex = 0)
	{
		_path = path;
		_waypointIndex = waypointIndex;
	}

	size_t GetWaypointIndex() const { return _waypointIndex; }

private:
	// 이동 및 등급 처리
	void followPath(float deltaTime);
	void spawnNextTier() const;

private:
	// 풍선 정보
	BloonColor _color = BloonColor::Red;
	int32 _hp = 1;
	Image* _image = nullptr;

	// 경로 정보
	const vector<Vector>* _path = nullptr;
	size_t _waypointIndex = 0;
};