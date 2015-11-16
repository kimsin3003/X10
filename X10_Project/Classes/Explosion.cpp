#include "stdafx.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "Explosion.h"

//Base Class of All Explosions

bool Explosion::init()
{
	radius = 0;
	maxRadius = 100;

	explosion = ParticleExplosion::create();
	explosion->setEmitterMode(kCCParticleModeGravity);
	explosion->setEmissionRate(500);
	explosion->setDuration(0.1);
	explosion->setLife(0.5);
	explosion->setSpeed(30);
	explosion->setSpeedVar(0);
	explosion->setEndSize(10);
	explosion->setStartSize(10);
	
	this->addChild(explosion);
	isFlying = true;
	lifeTime = 1.0 * Director::getInstance()->getFrameRate();
	return true;
}

void Explosion::Act(ColliderManager* cm)
{
	if (lifeTime > 0)
	{
		lifeTime--;
	}
	else
	{
		SetFlying(false);
		removeFromParent();
		cm->EraseCollider(this);
	}
}

void Explosion::SetFlying(bool flag)
{
	isFlying = flag;
}

bool Explosion::IsBullet()
{
	return false;
}

void Explosion::SetPosition(Point pos)
{
	setPosition(pos);
	explosion->setPosition(Point::ZERO);
}

const float& Explosion::GetBoundingRadius()
{
	radius += explosion->getSpeed()/ 2 / Director::getInstance()->getFrameRate();

	return radius;
}

