#pragma once
#include "BloonType.h"

class Bloon;

class BloonPopResolver
{
public:
	static int32 GetLayerHp(BloonColor color);

	// Bloon::SetHitHandler에 연결되는 델리게이트.
	// Bloon은 이 함수 시그니처만 알 뿐, 내부에서 hp 차감/사망 판정/자식 스폰이
	// 어떻게 이뤄지는지는 모른다.
	static void HandleHit(Bloon& bloon, float damage);

	// Bloon::SetLeakHandler에 연결되는 델리게이트.
	// 경로 끝(기지)까지 도달해 새어나갔을 때 호출된다.
	static void HandleLeak(Bloon& bloon);

	// 이 색의 풍선이 새어나갔을 때 플레이어가 입는 데미지.
	// 자기 자신 1 + 터졌다면 스폰됐을 모든 하위 풍선 개수를 재귀로 합산한다.
	static int32 GetLeakDamage(BloonColor color);

private:
	// 이번 히트로 살아남아 새로 소환될 풍선 하나 (관통 데미지로 여러 단계 내려간 뒤의 최종 hp)
	struct SpawnRequest
	{
		BloonColor color = BloonColor::Red;
		int32 hp = 0;
	};

	struct Result
	{
		bool popped = false;           // 이번 히트로 터졌는지
		int32 remainingHp = 0;         // popped == false 일 때 남은 hp
		vector<SpawnRequest> spawns;   // popped == true 일 때 생성할 자식 목록
		int32 totalGoldReward = 0;     // popped == true 일 때, 이번 히트로 실제 터진 모든 레이어의 골드 보상 합
	};

	static Result resolve(BloonColor color, int32 hp, int32 damage);
};
