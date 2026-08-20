#pragma once

#include "MovableActor.h"
#include "BloonType.h"
#include "Image.h"

struct CellInfo;

class Bloon : public MovableActor
{
	using Super = MovableActor;

public:
	// Bloon은 이 시그니처만 알 뿐, 실제로 무엇이 연결되는지는 모른다(BloonFactory가 조립).
	using HitHandler = std::function<void(Bloon&, float)>;
	// 경로 끝까지 도달해 새어나갔을 때 호출되는 델리게이트.
	using LeakHandler = std::function<void(Bloon&)>;

	// 초기화 및 업데이트
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphic& graphic) override;
	virtual void OnEnter(Actor* other) override;

	// 특수 풍선처럼 GameScene이 별도 시점에 직접 스프라이트만 그리고 싶을 때 사용.
	void RenderSprite(Graphic& graphic);

	// 풍선 정보
	BloonColor GetColor() const { return _color; }
	void SetColor(BloonColor color) { _color = color; }

	int32 GetHp() const { return _hp; }
	void SetHp(int32 hp) { _hp = hp; }
	void SetImage(Image* image) { _image = image; }
	// cellName이 있는 특수 풍선처럼 InGame.xml 아틀라스 셀을 그대로 쓸 때만 설정한다. 일반 풍선은 nullptr.
	void SetCell(const CellInfo* cell) { _cell = cell; }

	void SetHitHandler(HitHandler handler) { _hitHandler = std::move(handler); }
	void SetLeakHandler(LeakHandler handler) { _leakHandler = std::move(handler); }

	void ApplyDamage(float damage) { if (_hitHandler) _hitHandler(*this, damage); }

	// 경로 정보
	void SetPath(const vector<Vector>* path, size_t waypointIndex = 0)
	{
		_path = path;
		_waypointIndex = waypointIndex;
	}

	const vector<Vector>* GetPath() const { return _path; }
	size_t GetWaypointIndex() const { return _waypointIndex; }

private:
	// 이동 처리
	void followPath(float deltaTime);

private:
	// 풍선 정보
	BloonColor _color = BloonColor::Red;
	int32 _hp = 1;
	Image* _image = nullptr;
	const CellInfo* _cell = nullptr;
	HitHandler _hitHandler;
	LeakHandler _leakHandler;

	// 경로 정보
	const vector<Vector>* _path = nullptr;
	size_t _waypointIndex = 0;
};
