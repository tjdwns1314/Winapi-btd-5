#include "pch.h"
#include "BloonFactory.h"
#include "Bloon.h"

Bloon* BloonFactory::Create(ObjectPool<Bloon>& pool, BloonColor color, const Vector& pos, const vector<Vector>* path)
{
	Bloon* bloon = pool.Acquire();
	if (bloon == nullptr)
		return nullptr;

	bloon->SetColor(color);
	bloon->SetPos(pos);
	bloon->SetPath(path);
	bloon->Init();
	return bloon;
}
