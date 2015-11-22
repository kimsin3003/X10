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

	m_BulletNum = si->GetBulletCount();
	m_colliders.reserve(m_BulletNum);
	m_curBulletIndex = 0;

	hash_map<string, void*> bulletTypeInfo;
	bulletTypeInfo.insert(hash_map<string, void*>::value_type("CrossBullet", CrossBullet::create));
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

void ColliderManager::EraseDeadColliders()
{
	Collider* collider = nullptr;
	for (int i = 0; i < m_colliders.size(); i++)
	{
		collider = m_colliders.at(i);
		if (!collider->IsBullet() && collider->ToBeErased())
		{
			m_colliders.erase(m_colliders.begin() + i);
		}
	}
}

//반드시 쏠 불렛이 있는지 체크하고 불렛을 가져가야한다.
bool ColliderManager::HasBulletToShot()
{
	Bullet* bullet = nullptr;
	for (int i = 0; i < m_BulletNum; i++)
	{
		bullet = static_cast<Bullet*>(m_colliders.at(i));
		if(bullet->NotShooted())
		{
			return true;
		}
	}
	return false;
}

Bullet* ColliderManager::GetBulletToShot(Sling* sling)
{
	if (m_curBulletIndex < m_BulletNum)
	{
		Bullet* bullet = static_cast<Bullet*>(m_colliders.at(m_curBulletIndex));

		bullet->setPosition(sling->getPosition());
		bullet->setRotation(sling->GetRotationAngle());
		bullet->SetDirection(sling->GetDirection());
		bullet->SetSpeed(sling->GetSpeed());
		bullet->SetFlying(true);

		m_curBulletIndex++;

		return bullet;
	}
	return nullptr;
}