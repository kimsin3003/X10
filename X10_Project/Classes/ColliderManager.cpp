#include "stdafx.h"
#include "ColliderManager.h"
#include "Sling.h"
//colliders
#include "Collider.h"
#include "Bullet.h"
#include "CrossBullet.h"

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

	hash_map<string, void*> bulletTypeInfo;
	bulletTypeInfo.insert(hash_map<string, void*>::value_type("CrossBullet", CrossBullet::create));
	bulletTypeInfo.insert(hash_map<string, void*>::value_type("CrossBullet", CrossBullet::create));
	bulletTypeInfo.insert(hash_map<string, void*>::value_type("CrossBullet", CrossBullet::create));
	bulletTypeInfo.insert(hash_map<string, void*>::value_type("Bullet", Bullet::create));
	bulletTypeInfo.insert(hash_map<string, void*>::value_type("Bullet", Bullet::create));
	
	while (si->HasNextBullet())
	{
		//타겟 이름을 불러와서
		string type = si->GetCurrentBulletInfo();
		void* createFunction = bulletTypeInfo.at(type);
		
		//거기에 맞는 팩토리 함수 호출
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
		Bullet* bullet = (Bullet*)m_colliders.at(m_curBulletIndex++);
		
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

