#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"

BulletManager* BulletManager::instance = nullptr;

BulletManager::BulletManager() {
	Init();
}
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
void BulletManager::Init() //<- pass stage information parameter (si->BulletManger)
{										//that holds the number of bullets to have(not implemented yet)
	//temporary initialization for test
	curBulletIndex = 0;
	defaultBulletNum = 5;
	bullets.reserve(defaultBulletNum);

	InitBullets();
}

void BulletManager::InitBullets() //<- pass stage information parameter (si->Bullets) 
{								  //that holds what bullets to use (not implemented yet)

// ex
// bullets.pushBack(si->bullets->pop_back());
// bullets.pushBack(si->bullets->pop_back());
// bullets.pushBack(si->bullets->pop_back());
// bullets.pushBack(si->bullets->pop_back());
// ...
	bullets.pushBack(Bullet::create());
	bullets.pushBack(Bullet::create());
	bullets.pushBack(Bullet::create());
	bullets.pushBack(Bullet::create());
	bullets.pushBack(Bullet::create());

}

//call in gama manger's logic : GetBulletToShot -> add child & visible off & set position-> shot -> visible on
Bullet* BulletManager::GetBulletToShot()
{
	if (curBulletIndex < defaultBulletNum)
		return bullets.at(curBulletIndex++);
	return nullptr;
}

void BulletManager::AddExplosion(Bullet* explosion)
{
	bullets.pushBack(explosion);
}

bool BulletManager::HasNextBullet()
{
	if (curBulletIndex < defaultBulletNum)
		return true;
	return false;
}
