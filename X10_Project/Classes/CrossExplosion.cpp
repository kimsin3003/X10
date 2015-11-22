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

	return true;
}

void CrossExplosion::Act(ColliderManager* cm)
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

void CrossExplosion::RemoveSelf()
{
	SetFlying(false);
	removeFromParent();
}
