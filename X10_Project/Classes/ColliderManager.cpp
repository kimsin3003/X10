#include "stdafx.h"
#include "ColliderManager.h"
#include "Collider.h"
#include "Bullet.h"

ColliderManager* ColliderManager::instance = nullptr;

ColliderManager::ColliderManager() {
	Init();
}

ColliderManager::~ColliderManager() {}

ColliderManager* ColliderManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ColliderManager();
	}
	return instance;
}

//call in game manager's init
void ColliderManager::Init() //<- pass stage information parameter (si->ColliderManger)
{										//that holds the number of Colliders to have(not implemented yet)
	//temporary initialization for test
	curColliderIndex = 0;
	defaultColliderNum = 5;
	colliders.reserve(defaultColliderNum);

	InitColliders();
}

void ColliderManager::InitColliders() //<- pass stage information parameter (si->Colliders) 
{								  //that holds what Colliders to use (not implemented yet)

// ex
// Colliders.pushBack(si->Colliders->pop_back());
// Colliders.pushBack(si->Colliders->pop_back());
// Colliders.pushBack(si->Colliders->pop_back());
// Colliders.pushBack(si->Colliders->pop_back());
// ...

	colliders.pushBack(Bullet::create());
	colliders.pushBack(Bullet::create());
	colliders.pushBack(Bullet::create());
	colliders.pushBack(Bullet::create());
}

//call in gama manger's logic : GetColliderToShot -> add child & visible off & set position-> shot -> visible on
Collider* ColliderManager::GetColliderToShot()
{
	if (curColliderIndex < defaultColliderNum)
		return colliders.at(curColliderIndex++);
	return nullptr;
}

void ColliderManager::AddExplosion(Collider* explosion)
{
	colliders.pushBack(explosion);
}

bool ColliderManager::HasNextCollider()
{
	if (curColliderIndex < defaultColliderNum)
		return true;
	return false;
}

void ColliderManager::Reset()
{
	colliders.clear();
	Init();
}

