#include "stdafx.h"
#include "MoonExplosion.h"
#include "Explosion.h"

bool MoonExplosion::init()
{
	isFlying = false;
	particle = ParticleExplosion::create();
	particle->setVisible(false);
	this->addChild(particle);

	return true;
}

void MoonExplosion::Act()
{
	isFlying = true;
	particle->setVisible(true);
}

bool MoonExplosion::IsFlying()
{
	return isFlying;
}

void MoonExplosion::SetFlying(bool flag)
{
	isFlying = flag;
}