#pragma once
#include "Actor.h"
#include "ObstacleType.h"

class Image;
struct CellInfo;

class Obstacle : public Actor
{
	using Super = Actor;

public:
	virtual void Init() override;
	virtual void Render(Graphic& graphic) override;

	void SetType(ObstacleType type) { _type = type; }
	ObstacleType GetType() const { return _type; }

	// ObstacleFactory가 조립해서 넣어준다.
	void SetImage(Image* image) { _image = image; }
	void SetCell(const CellInfo* cell) { _cell = cell; }

	int32 GetSellPrice() const { return GetObstacleStat(_type).refundPrice; }

private:
	Image* _image = nullptr;
	const CellInfo* _cell = nullptr;

	ObstacleType _type = ObstacleType::BananaFarmTree;
};
