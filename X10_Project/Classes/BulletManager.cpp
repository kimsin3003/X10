#include "stdafx.h"
#include "BulletManager.h"

BulletManager* BulletManager::instance = nullptr;

BulletManager::BulletManager() {}
BulletManager::~BulletManager() {}

BulletManager* BulletManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BulletManager();
	}
	return instance;
}

//call in game manager's init
void BulletManager::initBulletManager() //<- pass stage information parameter (si->BulletManger)
{										//that holds the number of bullets to have(not implemented yet)
	//temporary initialization for test
	CurBulletIndex = 0;
	defaultBulletNum = 5;
	bullets.reserve(defaultBulletNum);

	initBullets();
}

void BulletManager::initBullets() //<- pass stage information parameter (si->Bullets) 
{								  //that holds what bullets to use (not implemented yet)

// ex
// bullets.push_back(si->bullets->pop_back());
// bullets.push_back(si->bullets->pop_back());
// bullets.push_back(si->bullets->pop_back());
// bullets.push_back(si->bullets->pop_back());
// ...

}

//call in gama manger's logic : GetBulletToShot -> add child & visible off & set position-> shot -> visible on
Bullet* BulletManager::GetBulletToShot()
{
	return bullets[CurBulletIndex++];
}