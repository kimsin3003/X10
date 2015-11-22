#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"

//Base Class of All Explosions

bool Explosion::init()
{
	m_radius = 0;
	m_maxRadius = 100;

	m_explosion = ParticleExplosion::create();
	m_explosion->setEmitterMode(kCCParticleModeGravity);
	m_explosion->setEmissionRate(500);
	m_explosion->setDuration(0.1);
	m_explosion->setLife(0.5);
	m_explosion->setSpeed(30);
	m_explosion->setSpeedVar(0);
	m_explosion->setEndSize(10);
	m_explosion->setStartSize(10);
	
	this->addChild(m_explosion);
	
	m_lifeTime = 1.0 * Director::getInstance()->getFrameRate();
	m_isFlying = true;
	m_toBeErased = false;

	return true;
}

void Explosion::Act()
{
	if (m_lifeTime > 0)
	{
		m_lifeTime--;
	}
	else
	{
		RemoveSelf();
	}
}

void Explosion::SetPosition(const Point& pos)
{
	setPosition(pos);
	m_explosion->setPosition(Point::ZERO);
}

void Explosion::RemoveSelf()
{
	SetFlying(false);
	removeFromParent();
	m_toBeErased = true;
}

const float& Explosion::GetBoundingRadius()
{
	m_radius += m_explosion->getSpeed() / 2 / Director::getInstance()->getFrameRate();

	return m_radius;
}