#pragma once

// 플레이어 골드(재화)를 관리한다.
// 싱글톤이 아니라 GameScene이 멤버로 소유하며, 씬이 새로 시작되면 함께 초기화된다.
// 타워 설치비 차감, 판매 환불, 업그레이드 비용 차감, 풍선 처치 보상 지급에 쓰인다.
class EconomyManager
{
public:
	void Init(int32 startGold);

	int32 GetGold() const { return _gold; }

	// 잔액이 amount 이상이면 차감하고 true, 부족하면 아무것도 하지 않고 false.
	bool TrySpend(int32 amount);

	void Add(int32 amount);

private:
	int32 _gold = 0;
};
