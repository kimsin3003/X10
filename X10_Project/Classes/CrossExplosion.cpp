#include "stdafx.h"
#include "Explosion.h"
#include "CrossExplosion.h"
#include "ColliderManager.h"

bool CrossExplosion::init()
{
	m_radius = 0;
	m_maxRadius = 100;
	m_isFlying = true;
	m_lifeTime = 5 * Director::getInstance()->getFrameRate();

	InitLings();

	return true;
}

void CrossExplosion::Act(ColliderManager* cm)
{
	if (m_lifeTime > 0)
	{
		if (m_curLingIdx < lingNum && m_lingBeginTime >= m_lifeTime)
			AddLings();
	
		m_lifeTime--;
	}
	else
	{
		RemoveSelf();
	}
}

void CrossExplosion::RemoveSelf()
{
	SetFlying(false);
	for (int i = 0; i < lingNum; i++)
	{
		ParticleExplosion* ling = m_crossLings.at(i);
		ling->removeFromParent();
	}
	m_crossLings.clear();
	removeFromParent();
}

void CrossExplosion::AddLings()
{
	ParticleExplosion* ling = m_crossLings.at(m_curLingIdx);
	addChild(ling);
	SetLingDefault(ling);

	switch (m_curLingIdx)
	{
	case 0:
		ling->setPosition(0, 0);
		m_lingBeginTime -= lingBeginDelta;
		break;
	case 1:
		ling->setPosition(0, lingPosDelta);
		m_lingBeginTime -= lingBeginDelta;
		break;
	case 2:
		ling->setPosition(-lingPosDelta, lingPosDelta);
		break;
	case 3:
		ling->setPosition(lingPosDelta, lingPosDelta);
		m_lingBeginTime -= lingBeginDelta;
		break;
	case 4:
		ling->setPosition(0, 2*lingPosDelta);
		break;
	}

	m_curLingIdx++;
}

void CrossExplosion::InitLings()
{
	m_curLingIdx = 0;

	m_crossLings.reserve(lingNum);
	for (int i = 0; i < lingNum; i++)
	{
		m_crossLings.pushBack(ParticleExplosion::create());
	}

	m_lingBeginTime = m_lifeTime;
}

void CrossExplosion::SetLingDefault(ParticleExplosion* ling)
{
	ling->setEmitterMode(kCCParticleModeGravity);
	ling->setEmissionRate(500);
	ling->setDuration(0.1);
	ling->setLife(0.3);
	ling->setSpeed(30);
	ling->setSpeedVar(0);
	ling->setEndSize(10);
	ling->setStartSize(10);
}

const float& CrossExplosion::GetBoundingRadius()
{
	m_radius = 10 * m_curLingIdx / Director::getInstance()->getFrameRate();

	return m_radius;
}

