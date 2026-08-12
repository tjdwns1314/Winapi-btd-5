#include "pch.h"
#include "EconomyManager.h"

void EconomyManager::Init(int32 startGold)
{
	_gold = startGold;
}

bool EconomyManager::TrySpend(int32 amount)
{
	if (_gold < amount)
		return false;

	_gold -= amount;
	return true;
}

void EconomyManager::Add(int32 amount)
{
	_gold += amount;
}
