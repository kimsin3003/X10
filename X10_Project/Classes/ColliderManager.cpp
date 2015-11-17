#include "stdafx.h"
#include "ColliderManager.h"
#include "Sling.h"
//colliders
#include "Collider.h"
#include "Bullet.h"
//Stage Information
#include "StageInformation.h"
#include <hash_map>
using namespace stdext;

void ColliderManager::InitBullets(StageInformation* si)
{
	ResetBullets();

	m_defaultBulletNum = si->GetBulletCount();
	m_colliders.reserve(m_defaultBulletNum);
	m_curBulletIndex = 0;

	hash_map<string, void*> bulletTypeInfo; ///# void*는 네버에버 쓰지마라.. 

	bulletTypeInfo.insert(hash_map<string, void*>::value_type("Bullet", Bullet::create));
	while (si->HasNextBullet())
	{
		//타겟 이름을 불러와서
		string type = si->GetCurrentBulletInfo();
		void* createFunction = bulletTypeInfo.at(type);
		
		//거기에 맞는 팩토리 함수 호출

		///# C++ 에서는 아주 구형 컴파일러만 쓸 수 있는 상황이 아니라면, 함수 포인터는 쓰지 않는데. 
		/// 이 기회에 std::function 및 std::bind에 대해 공부하고 이 부분을 모두 이걸로 바꾸어 볼 것!
		Bullet* (*create)() = static_cast<Bullet* (*)()>(createFunction);
		Bullet* bullet = (*create)();

		//리스트에 넣음.
		m_colliders.pushBack(bullet);
	}
	
}

Bullet* ColliderManager::GetBulletToShot(Sling* sling)
{
	if (m_curBulletIndex < m_defaultBulletNum)
	{
		Bullet* bullet = (Bullet*)m_colliders.at(m_curBulletIndex++); ///# C-style 캐스팅 쓰지 말 것.
		
		bullet->setPosition(sling->getPosition());
		bullet->setRotation(sling->GetRotationAngle());
		bullet->SetDirection(sling->GetDirection());
		bullet->SetSpeed(sling->GetSpeed());
		bullet->SetFlying(true);

		return bullet;
	}

	return nullptr;
}

void ColliderManager::AddExplosion(Collider* explosion)
{
	m_colliders.pushBack(explosion);
}

void ColliderManager::ResetBullets()
{
	for (Collider* collider : m_colliders)
	{
		delete collider;
	}
	m_colliders.clear();
}
void ColliderManager::EraseCollider(Collider* collider)
{
	m_colliders.eraseObject(collider);
}

bool ColliderManager::HasBullet()
{
	if (m_curBulletIndex < m_defaultBulletNum)
	{
		return true;
	}
	return false;
}

