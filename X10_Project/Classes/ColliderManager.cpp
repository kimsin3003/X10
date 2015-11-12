#include "stdafx.h"
#include "ColliderManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sling.h"

void ColliderManager::Init()
{										
	curBulletIndex = 0;
	defaultBulletNum = 5;
	colliders.reserve(defaultBulletNum);

	InitColliders();
}

void ColliderManager::InitColliders()
{						

	for (int i = 0; i < defaultBulletNum; i++)
	{
		colliders.pushBack(Bullet::create());
	}
}

Bullet* ColliderManager::GetBulletToShot()
{
	if (curBulletIndex < defaultBulletNum)
	{
		Sling* sling = Sling::GetInstance();
		Bullet* bullet = (Bullet*)colliders.at(curBulletIndex++);
		
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
	colliders.pushBack(explosion);
}

bool ColliderManager::HasBullet()
{
	if (curBulletIndex < defaultBulletNum)
	{
		return true;
	}
	return false;
}

void ColliderManager::Reset()
{
	colliders.clear(); ///# 헐? Collider* 원소들은 다 메모리 누수 나겠네..
	Init();
}

void ColliderManager::EraseCollider(Collider* collider)
{
	colliders.eraseObject(collider);
}