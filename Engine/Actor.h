#pragma once
class Actor
{
public: 
	virtual ~Actor();

	void Init();
	virtual void Destroy();
	virtual void Update(float deltaTime);
	virtual void Render(HDC hdc);

	virtual void OnEnter(Actor* other) {}
	virtual void OnStay(Actor* other) {}
	virtual void OnExit(Actor* other) {}

	Vector GetPos() const { return _pos; }
	void SetPos(const Vector& pos) { _pos = pos; }
	float GetRotation() const { return _rotation; }
	Vector GetScale() const { return _scale;}

private :

	string _name;
	class Scene* _owner;
	int _layer;
	bool _active = true;

	Vector _pos;
	Vector _scale = { 1.f, 1.f };
	float _rotation = 0.f;


	bool _pendingKill = false;
	//IObjectPool* _pool = nullptr;
	//vector<class Component*> _components;

};

