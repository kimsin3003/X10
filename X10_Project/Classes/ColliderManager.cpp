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
	for (int i = 0; i < defaultColliderNum; i++)
	{
		colliders.pushBack(Bullet::create()); ///# 내부에서 new를 해서 벡터에 넣기 때문에 자원해제는 반드시 따로 해줘야 한다.
	}
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
	colliders.clear(); ///# 헐? Collider* 원소들은 다 메모리 누수 나겠네..
	Init();
}


