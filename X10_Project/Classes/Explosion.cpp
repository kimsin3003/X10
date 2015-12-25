#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"
#include <SimpleAudioEngine.h>

Explosion::Explosion() : m_explosion(nullptr),
		m_lifeDecrease(-1), m_lifeTime(-1), m_radius(-1), m_maxRadius(-1)
{

}

bool Explosion::init()
{
	m_radius = 0;
	m_maxRadius = DEFAULT_RADIUS;

	m_lifeTime = 4.0f;
	m_lifeDecrease = Director::getInstance()->getDeltaTime();
	m_isFlying = true;
	m_toBeErased = false;
	  
	m_explosion = ParticleExplosion::create();
	m_explosion->setColor(Color3B());
	m_explosion->setEmitterMode(kCCParticleModeGravity);
	m_explosion->setEmissionRate(400);
	m_explosion->setDuration(m_lifeTime/15);
	m_explosion->setLife(m_lifeTime);
	m_explosion->setEndSize(10);
	m_explosion->setStartSize(10);
	m_explosion->setStartSizeVar(0);
	m_explosion->setEndSizeVar(0);
	m_explosion->setSpeedVar(0);
	m_explosion->setSpeed(m_maxRadius / m_lifeTime);
	m_explosion->setPosition(Point::ZERO);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/sound_effects/firework_explosion3.mp3", false, 1.0f, 0, 0);
	this->addChild(m_explosion);
	
	return true;
}

void Explosion::Act()
{
	if (m_lifeTime > 0)
	{
		m_lifeTime -= m_lifeDecrease;
	}
	else
	{
		RemoveSelf();
	}
}

void Explosion::RemoveSelf()
{
	m_isFlying = false;
	m_toBeErased = true;
	removeFromParent();
}

const float& Explosion::GetBoundingRadius()
{
	//���� radius ��� �ؼ� ��ȯ��. (������ ũ�� - ó��ũ��) * �����ð����� + ó��ũ��
	float maxLife = m_explosion->getLife();
	float speedOfParticle = m_explosion->getSpeed();
	return speedOfParticle * (1 - m_lifeTime / maxLife) * maxLife;
}