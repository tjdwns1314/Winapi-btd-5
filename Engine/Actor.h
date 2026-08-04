#pragma once

// 렌더링은 GDI가 아니라 Direct2D를 사용하므로 HDC 대신 Graphic을 넘긴다.
class Graphic;

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

	int32 GetLayer() const { return _layer; }
	void SetLayer(int32 layer) { _layer = layer; }

	bool IsActive() const { return _active; }
	void SetActive(bool active) { _active = active; }

	// 순회 도중 바로 지우면 이터레이터가 깨지므로,
	// 죽음 표시만 해두고 실제 제거는 Scene::PostUpdate에서 처리한다.
	bool IsPendingKill() const { return _pendingKill; }
	void SetPendingKill() { _pendingKill = true; }

private :

	string _name;
	class Scene* _owner = nullptr;
	int32 _layer = static_cast<int32>(RenederLayer::Background);
	bool _active = true;

	Vector _pos;
	Vector _scale = { 1.f, 1.f };
	float _rotation = 0.f;


	bool _pendingKill = false;
	//IObjectPool* _pool = nullptr;
	//vector<class Component*> _components;

};

