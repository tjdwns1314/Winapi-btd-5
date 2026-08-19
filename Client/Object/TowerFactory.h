#pragma once
#include "TowerType.h"
#include "ObjectPool.h"

class Tower;

// Tower 생성 + 초기화(종류별 이미지 조립)를 한 곳에 모은다.
// Scene 등록은 호출부 책임.
class TowerFactory
{
public:
	static Tower* Create(ObjectPool<Tower>& pool, TowerType type, const Vector& pos);
};
