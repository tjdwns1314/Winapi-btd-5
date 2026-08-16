#pragma once
#include "Actor.h"
#include "Bloon.h"
#include "TowerType.h"
#include "TowerFireBehavior.h"

class Image;
struct CellInfo;
class GameScene;

class Tower : public Actor
{
	using Super = Actor;

public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;
	
	void SetType(TowerType type) { _type = type; }
	TowerType GetType() const { return _type; }

	// TowerFactory가 종류별로 필요한 리소스를 조립해서 넣어준다.
	void SetImage(Image* image) { _image = image; }
	void SetCell(const CellInfo* cell) { _cell = cell; }
	void SetBakedImage(Image* bakedImage) { _bakedImage = bakedImage; }

	// TowerFactory가 GetTowerStat()으로 조회한 스탯을 통째로 복사해서 넣어준다.
	// 복사본이라 업그레이드 등으로 개체별로 값이 바뀌어도 같은 타입의 다른 타워에 영향 없다.
	void SetTowerData(const TowerStat& data) 
	{ _towerData = &data; _stat = data.grades.front(); }
	const TowerStat& GetTowerData() const { return *_towerData; }
	const TowerGradeStat& GetStat() const { return _stat; }


	int32 GetGrade() const { return _grade; }
	bool CanUpgrade() const { return _canUpgrade; }
	int32 GetSellPrice() const { return _towerData->refundPrice; }
	int32 GetNextUpgradeCost() const;
	void ApplyUpgrade();



	// TowerFactory가 종류별 발사 함수를 꽂아준다.
	void SetFireBehavior(FireBehaviorFn behavior) { _fireBehavior = behavior; }
	// TowerFactory가 종류별 애니메이션 프레임 키 함수를 꽂아준다. nullptr이면 애니메이션 없음.
	void SetFrameKeyFn(TowerFrameKeyFn fn) { _frameKeyFn = fn; }

	// 발사 함수(TowerFireBehavior.cpp)가 접근해야 하는 것들.
	Bloon* GetTarget() const { return _target; }
	GameScene* GetGameScene() const;
	// 애니메이션이 있는 타워는 던지기 도중인 손 위치, 없는 타워는 중심 위치를 반환한다.
	Vector GetFirePos() const;

private:
	void RenderRange(Graphic& graphic) const;
	bool isInRange(const Actor* target) const;
	Bloon* findTarget() const;
	void fire();
	void updateThrowAnimation(float deltaTime);
	Vector getHandLocalOffset() const;

	Image* _image = nullptr;
	Image* _bakedImage = nullptr; // 여러 스프라이트를 합성해 구운 텍스처를 쓰는 타워용. nullptr이면 기존 방식(_cell) 사용.

	const CellInfo* _cell = nullptr;
	Bloon* _target = nullptr;

	TowerType _type = TowerType::DartMonkey;
	const TowerStat* _towerData = nullptr; // 타입별 고정값 + 등급표(정적 테이블을 가리킴).
	TowerGradeStat _stat{};                // 현재 등급 스탯. ApplyUpgrade()마다 _towerData->grades[i]로 교체.
	
	FireBehaviorFn _fireBehavior = nullptr;
	TowerFrameKeyFn _frameKeyFn = nullptr; // non-null이면 애니메이션 있는 타워.

	float _fireTimer = 0.f;	// 콜리전 매니저로 실제 사거리 판정을 붙이기 전까지, 주기 발사 타이머로만 사용

	int32 _grade = 1;			// 현재 등급, 1부터 시작 (스탯이 아니라 이 타워 개체의 진행 상태)

	bool _canUpgrade = true;	// 다음 등급으로 업그레이드 가능 여부(최고 등급이면 false)

	// 프레임 애니메이션 재생 상태. _frameKeyFn이 nullptr인 타워는 사용하지 않는다.
	bool _isThrowing = false;
	int32 _animFrame = 0;		// 0 ~ (_throwFrameCount - 1). 프레임 이름 규칙은 타워 타입마다 다름(_frameKeyFn 참고).
	float _animTimer = 0.f;
	int32 _throwFrameCount = 1;	// 현재 던지기 사이클의 총 프레임 수. _isThrowing 시작 시점에 _frameKeyFn 반환값으로 캐싱.
};
