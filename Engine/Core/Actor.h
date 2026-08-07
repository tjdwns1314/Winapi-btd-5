#pragma once

// 렌더링은 GDI가 아니라 Direct2D를 사용하므로 HDC 대신 Graphic을 넘긴다.
class Graphic;
class IObjectPool;
class Collider;

class Actor
{
public:
	virtual ~Actor();

	virtual void Init();
	virtual void Destroy();
	virtual void Update(float deltaTime);
	virtual void Render(Graphic& graphic);

	virtual void OnEnter(Actor* other) {}
	virtual void OnStay(Actor* other) {}
	virtual void OnExit(Actor* other) {}

	// 콜라이더가 없는 Actor(Tower 등)는 기본적으로 nullptr을 반환한다.
	virtual Collider* GetCollider() const { return nullptr; }

	ActorType GetActorType() const { return _actorType; }

	Vector GetPos() const { return _pos; }
	void SetPos(const Vector& pos) { _pos = pos; }
	float GetRotation() const { return _rotation; }
	void SetRotation(float rotation) { _rotation = rotation; }
	Vector GetScale() const { return _scale;}
	void SetScale(const Vector& scale) { _scale = scale; }

	const string& GetName() const { return _name; }
	void SetName(const string& name) { _name = name; }

	class Scene* GetOwner() const { return _owner; }
	void SetOwner(class Scene* owner) { _owner = owner; }

	RenderLayer GetLayer() const { return _layer; }
	void SetLayer(RenderLayer layer) { _layer = layer; }

	bool IsActive() const { return _active; }
	void SetActive(bool active) { _active = active; }

	// 순회 도중 바로 지우면 이터레이터가 깨지므로,
	// 죽음 표시만 해두고 실제 제거는 Scene::PostUpdate에서 처리한다.
	bool IsPendingKill() const { return _pendingKill; }
	void SetPendingKill() { _pendingKill = true; }

	void SetPool(IObjectPool* pool) { _pool = pool; }
	IObjectPool* GetPool() const { return _pool; }

protected:
	void SetActorType(ActorType type) { _actorType = type; }

private :

	string _name;
	class Scene* _owner = nullptr;
	RenderLayer _layer = RenderLayer::Background;
	bool _active = true;
	ActorType _actorType = ActorType::Count;

	Vector _pos;
	Vector _scale = { 1.f, 1.f };
	float _rotation = 0.f;


	bool _pendingKill = false;
	IObjectPool* _pool = nullptr;
	//vector<class Component*> _components;

};

