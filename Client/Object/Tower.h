#pragma once
#include "Actor.h"
#include "Bloon.h"

class Image;
struct CellInfo;

class Tower : public Actor
{
	using Super = Actor;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;
private:

	void RenderRange(Graphic& graphic) const;
	Bloon* findTarget() const;
	bool isInRange(const Actor* target) const;
	void fire();
	static const char* GetSpriteName();


	Image* _image = nullptr;
	const CellInfo* _cell = nullptr;
	Bloon* _target = nullptr;

	float _fireTimer = 0.f;	// 콜리전 매니저로 실제 사거리 판정을 붙이기 전까지, 주기 발사 타이머로만 사용

	float _attackRange = BLOCK_SIZE * 7.f;	// 공격 사거리 (placeholder: 그리드 2칸 분량, 실제 밸런스 값은 추후 조정 예정)
	float _damage = 1.f;		// 공격 데미지 (placeholder)
	float _attackSpeed = 1.f;	// 공격 속도(초당 공격 횟수 또는 공격 주기) (placeholder)
	int32 _grade = 1;			// 현재 등급, 1부터 시작
	bool _canUpgrade = true;	// 다음 등급으로 업그레이드 가능 여부(최고 등급이면 false)
	int32 _upgradeCost = 0;		// 다음 등급으로 올리는 데 필요한 비용
	int32 _attackCount = 1;		// 한 번의 공격으로 명중시킬 수 있는 풍선 개수

};

