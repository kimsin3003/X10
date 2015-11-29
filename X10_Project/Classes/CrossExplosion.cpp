#include "stdafx.h"
#include "Explosion.h"
#include "CrossExplosion.h"

bool CrossExplosion::init()
{
	m_lifeTime = 1.0;
	m_isFlying = true;
	m_toBeErased = false;
	
	m_radius = 0;
	m_maxRadius = 2.5f;

	m_explosion = ParticleExplosion::create();
	m_explosion->setEmitterMode(kCCParticleModeRadius);
	m_explosion->setEmissionRate(150);
	m_explosion->setDuration(0.1f);
	m_explosion->setLife(1.0f);
	m_explosion->setEndSize(25.0f);
	m_explosion->setStartSize(25.0f);
	m_explosion->setPosition(Point::ZERO);

	this->addChild(m_explosion);

	return true;
}