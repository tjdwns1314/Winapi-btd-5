#pragma once

// 플레이어 체력(생명력)을 관리한다.
// 싱글톤이 아니라 GameScene이 멤버로 소유하며, 씬이 새로 시작되면 함께 초기화된다.
// 풍선이 경로 끝(기지)까지 도달해 새어나갈 때 데미지를 받는다.
class HealthManager
{
public:
	void Init(int32 startHp);

	int32 GetHp() const { return _hp; }
	bool IsGameOver() const { return _hp <= 0; }

	// 풍선이 새어나갔을 때 호출. 0 밑으로는 내려가지 않는다.
	void TakeDamage(int32 amount);

	// 디버그/치트용 체력 증가. 상한 없음.
	void Add(int32 amount);

private:
	int32 _hp = 0;
};
