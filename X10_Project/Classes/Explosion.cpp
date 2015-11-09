#include "stdafx.h"
#include "Explosion.h"

bool Explosion::init()
{
	isFlying = false;
	particle = ParticleExplosion::create();
	particle->setVisible(false);
	this->addChild(particle);

	return true;
}

void Explosion::Act()
{
	isFlying = true;
	particle->setVisible(true);
}

bool Explosion::IsFlying()
{
	return isFlying;
}

void Explosion::SetFlying(bool flag)
{
	isFlying = flag;
}