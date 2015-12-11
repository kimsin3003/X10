#include "stdafx.h"
#include "ColliderManager.h"
#include "Sling.h"
//colliders
#include "Collider.h"
#include "Bullet.h"
#include "CrossBullet.h"

//Stage Information
#include "StageInformation.h"
#include <unordered_map>
using namespace stdext;

void ColliderManager::InitBullets(StageInformation* si)
{
	ResetBullets();

	m_BulletNum = si->GetBulletCount();
	m_colliders.reserve(m_BulletNum);
	m_curBulletIndex = 0;

	typedef unordered_map<string, function<Bullet*()>> BulletInfoMap;
	BulletInfoMap bulletTypeInfo; //string�� Ÿ�� �̸�.
	bulletTypeInfo.insert(BulletInfoMap::value_type("Bullet", Bullet::create));
	bulletTypeInfo.insert(BulletInfoMap::value_type("CrossBullet", CrossBullet::create));

	while (si->HasNextBullet())
	{
		//Ÿ�� �̸��� �ҷ��ͼ�
		string type = si->GetCurrentBulletInfo();
		auto createFunction = bulletTypeInfo.at(type);
		
		//�ű⿡ �´� ���丮 �Լ� ȣ��
		Bullet* bullet = createFunction();

		//����Ʈ�� ����.
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
		if (collider->ToBeErased())
		{
			if (collider->IsBullet())
			{
				m_BulletNum--;
				m_curBulletIndex--;
			}
			m_colliders.erase(m_colliders.begin() + i);
		}
	}
}

bool ColliderManager::HasBulletToShot()
{
	Bullet* bullet = nullptr;
	for (int i = 0; i < m_BulletNum; i++)
	{
		bullet = static_cast<Bullet*>(m_colliders.at(i));
		if (bullet->IsActionStopped() == false && bullet->IsFlying() == false)
		{
			m_curBulletIndex = i;
			return true;
		}
	}
	m_curBulletIndex = -1;
	return false;
}

Bullet* ColliderManager::GetBulletToShot(Sling* sling)
{
	if (m_curBulletIndex != -1)
	{
		Bullet* bullet = static_cast<Bullet*>(m_colliders.at(m_curBulletIndex));

		bullet->setPosition(sling->getPosition());
		bullet->setRotation(sling->GetRotationAngle());
		bullet->SetDirection(sling->GetDirection());
		bullet->SetStartSpeed(sling->GetSpeed());
		bullet->SetFlying(true);

		return bullet;
	}

	return nullptr;
}

bool ColliderManager::HasCollider()
{
	if (m_colliders.size() == 0)
		return false;

 	return true;
}