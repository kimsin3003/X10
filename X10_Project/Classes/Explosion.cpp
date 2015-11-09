#include "stdafx.h"
#include "Explosion.h"

bool Explosion::init()
{
	isFlying = false;
	particle = ParticleExplosion::create();
	this->addChild(particle);
	//this->setPosition()
	return true;
}

void Explosion::Act()
{

}

bool Explosion::IsFlying()
{
	return isFlying;
}

void Explosion::SetFlying(bool flag)
{
	isFlying = flag;
}
