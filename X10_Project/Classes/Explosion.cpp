#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"
#include "ColliderManager.h"

//Base Class of All Explosions
bool Explosion::init()
{
	isFlying = true;
	particle = ParticleExplosion::create();
	particle->setVisible(true);
	this->addChild(particle);
	lifeTime = 2 * Director::getInstance()->getFrameRate();
	return true;
}

void Explosion::Act()
{
	if (lifeTime > 0){
		lifeTime--;
	}
	else{

		particle->setVisible(false);
		isAlive = false;
		isFlying = false;
		removeFromParent();
		Vector<Collider*> list = ColliderManager::GetInstance()->GetColliders();
		list.eraseObject(this, true);
	}
}

void Explosion::SetPosition(Vec2 position)
{
	setPosition(position);
	particle->setPosition(position);
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

bool Explosion::IsAlive()
{
	return isAlive;
}
