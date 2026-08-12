#include "pch.h"
#include "HealthManager.h"

void HealthManager::Init(int32 startHp)
{
	_hp = startHp;
}

void HealthManager::TakeDamage(int32 amount)
{
	_hp -= amount;
	if (_hp < 0)
		_hp = 0;
}
