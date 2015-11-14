#include "stdafx.h"
#include "Collider.h"
#include "ColliderManager.h"
#include "Explosion.h"

//Base Class of All Explosions

bool Explosion::init()
{
	explosion = ParticleExplosion::create();
	explosion->setEmitterMode(kCCParticleModeGravity);
	this->addChild(explosion);
	isFlying = true;
	radius = 0;
	lifeTime = 0.5 * Director::getInstance()->getFrameRate();
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
	radius += (explosion->getSpeedVar() + 10) / Director::getInstance()->getFrameRate();

	return radius;
}

