#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"

//Base Class of All Explosions
bool Explosion::init()
{
	isFlying = false;
	particle = ParticleExplosion::create();
	particle->setVisible(false);
	this->addChild(particle);
	lifeTime = 10 * Director::getInstance()->getFrameRate();
	return true;
}

void Explosion::Act()
{
	if (lifeTime-- > 0){
		isFlying = true;
		particle->setVisible(true);
	}
	else{
		particle->setVisible(false);
		isFlying = false;
		this->removeFromParent();
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

