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

	defaultBulletNum = si->GetBulletCount();
	colliders.reserve(defaultBulletNum);
	curBulletIndex = 0;

	for (int i = 0; i < defaultBulletNum; i++)
	{
		colliders.pushBack(Bullet::create());
	}
	/*
	hash_map<string, void*> targetTypeInfo;
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Bullet", Bullet::create));
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Bullet", Bullet::create));
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Bullet", Bullet::create));
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Bullet", Bullet::create));
	targetTypeInfo.insert(hash_map<string, void*>::value_type("Bullet", Bullet::create));

	while (si->HasNextBullet())
	{
		
	}
	*/
}

Bullet* ColliderManager::GetBulletToShot(Sling* sling)
{
	if (curBulletIndex < defaultBulletNum)
	{
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

void ColliderManager::ResetBullets()
{
	for (Collider* collider : colliders)
	{
		delete collider;
	}
	colliders.clear();
}
void ColliderManager::EraseCollider(Collider* collider)
{
	colliders.eraseObject(collider);
}

bool ColliderManager::HasBullet()
{
	if (curBulletIndex < defaultBulletNum)
	{
		return true;
	}
	return false;
}

