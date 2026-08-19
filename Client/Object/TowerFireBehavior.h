#pragma once
#include "TowerType.h"

class Tower;

// 타워 종류별 발사 패턴(단일 타겟 추적, 8방향 전방위 등)을 함수로 분리해서 주입한다.
// Tower는 이 함수를 호출만 할 뿐, 발사 방식 자체는 모른다.
using FireBehaviorFn = void(*)(Tower&);

FireBehaviorFn GetFireBehavior(TowerType type);
