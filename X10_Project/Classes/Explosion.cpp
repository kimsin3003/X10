#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"

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

bool Explosion::IsAlive()
{
	return isAlive;
}
