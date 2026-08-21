#include "pch.h"
#include "BloonFactory.h"
#include "Bloon.h"
#include "BloonPopResolver.h"
#include "ResourceManager.h"

namespace
{
	Image& getBloonImage(const wstring& spriteKey)
	{
		const wstring path = L"Resource\\" + spriteKey + L".png";
		return ResourceManager::GetInstance().GetImage(path.c_str());
	}
}

Bloon* BloonFactory::Create(ObjectPool<Bloon>& pool, BloonColor color, const Vector& pos, const vector<Vector>* path, size_t waypointIndex)
{
	Bloon* bloon = pool.Acquire();
	if (bloon == nullptr)
		return nullptr;

	const BloonStat& stat = GetBloonStat(color);

	bloon->SetColor(color);
	bloon->SetPos(pos);
	bloon->SetPath(path, waypointIndex);
	bloon->SetHp(stat.layerHp);
	bloon->SetMoveSpeed(stat.speed);

	if (stat.cellName.empty())
	{
		bloon->SetCell(nullptr);
		bloon->SetImage(&getBloonImage(stat.spriteKey));
	}
	else
	{
		// cellName이 있으면 별도 스프라이트 파일 없이 InGame.xml 아틀라스 셀을 그대로 쓴다.
		ResourceManager& res = ResourceManager::GetInstance();
		bloon->SetImage(&res.GetImage(L"Resource\\Sprite\\InGame.png"));
		bloon->SetCell(res.GetAtlas(L"Resource\\Sprite\\InGame.xml").GetCell(stat.cellName));
	}

	bloon->SetHitHandler(&BloonPopResolver::HandleHit);
	bloon->SetLeakHandler(&BloonPopResolver::HandleLeak);
	bloon->Init();
	return bloon;
}
