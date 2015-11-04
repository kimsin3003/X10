#include "stdafx.h"
#include "BulletManager.h"

BulletManager* BulletManager::instance = nullptr;

BulletManager* BulletManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BulletManager();
	}
	return instance;
}

