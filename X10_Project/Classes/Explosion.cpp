#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"
#include "ColliderManager.h"

//Base Class of All Explosions
bool Explosion::init()
{
	particle = ParticleExplosion::create();
	this->addChild(particle);
	isFlying = true;
	lifeTime = 2 * Director::getInstance()->getFrameRate();
	return true;
}

void Explosion::Act()
{
	if (lifeTime > 0)
	{
		lifeTime--;
	}
	else
	{
		SetFlying(false);
		removeFromParent();
		ColliderManager::GetInstance()->EraseCollider(this);
	}
}

bool Explosion::IsFlying()
{
	return isFlying;
}

void Explosion::SetFlying(bool flag)
{
	isFlying = flag;
}

bool Explosion::IsBullet()
{
	return false;
}

