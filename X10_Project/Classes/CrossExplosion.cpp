#include "stdafx.h"
#include "Explosion.h"
#include "CrossExplosion.h"
#include "ColliderManager.h"

bool CrossExplosion::init()
{
	Explosion::init();
	return true;
}

void CrossExplosion::Act()
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
