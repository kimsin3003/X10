#include "stdafx.h"
#include "BulletManager.h"

BulletManager* BulletManager::instance = new BulletManager();

BulletManager::BulletManager()
{
	instance = new BulletManager();
}


BulletManager::~BulletManager()
{
}

BulletManager* BulletManager::GetInstance()
{
	if (instance == nullptr)
		instance = new BulletManager();
	return instance;
}
