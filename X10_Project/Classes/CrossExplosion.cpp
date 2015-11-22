#include "stdafx.h"
#include "Explosion.h"
#include "CrossExplosion.h"

bool CrossExplosion::init()
{
	m_radius = 0;
	m_maxRadius = 25;

	m_explosion = ParticleExplosion::create();
	m_explosion->setEmitterMode(kCCParticleModeGravity);
	m_explosion->setEmissionRate(250);
	m_explosion->setDuration(0.75f);
	m_explosion->setLife(0.40f);
	m_explosion->setSpeed(25);
	m_explosion->setSpeedVar(1);
	m_explosion->setEndSize(5);
	m_explosion->setStartSize(3);

	this->addChild(m_explosion);

	m_lifeTime = 1.0 * Director::getInstance()->getFrameRate();
	m_isFlying = true;
	m_toBeErased = false;

	return true;
}