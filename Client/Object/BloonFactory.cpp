#include "pch.h"
#include "BloonFactory.h"
#include "Bloon.h"

Bloon* BloonFactory::Create(BloonColor color, const Vector& pos, const vector<Vector>* path)
{
	Bloon* bloon = new Bloon();
	bloon->SetColor(color);
	bloon->SetPos(pos);
	bloon->SetPath(path);
	bloon->Init();
	return bloon;
}
