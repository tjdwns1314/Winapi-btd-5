#pragma once
#include "Actor.h"
#include <memory>

class IObjectPool
{
public:
	virtual ~IObjectPool() = default;
	virtual void Return(Actor* actor) = 0;
};

template<typename T>
class ObjectPool : public IObjectPool
{
public:
	void Init(size_t size)
	{
		_buffer.clear();
		_available.clear();

		_buffer.resize(size);
		_available.reserve(size);

		for (T& obj : _buffer)
		{
			obj.SetPool(this);
			_available.push_back(&obj);
		}
	}

	T* Acquire()
	{
		if (_available.empty())
			return nullptr;

		T* obj = _available.back();
		_available.pop_back();

		// 재사용 직전에 파괴 후 재생성해서 이전 사용 흔적(필드 잔류, 소유 리소스)을
		// 남김없이 지운다. Factory가 Setter를 하나 빠뜨려도 잔류 상태가 새어나가지 않는다.
		std::destroy_at(obj);
		std::construct_at(obj);
		obj->SetPool(this);

		return obj;
	}

	virtual void Return(Actor* actor) override
	{
		_available.push_back(static_cast<T*>(actor));
	}

private:
	vector<T> _buffer;
	vector<T*> _available;
};
