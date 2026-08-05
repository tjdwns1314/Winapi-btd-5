#pragma once
#include "Actor.h"

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
