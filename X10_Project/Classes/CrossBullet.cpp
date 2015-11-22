#include "stdafx.h"
#include "Bullet.h"
#include "CrossBullet.h"
#include "Explosion.h"
#include "CrossExplosion.h"

bool CrossBullet::init()
{
	Bullet::init();

	m_timeToExplode = 10;

	return true;
}

void CrossBullet::Act()
{
	if (m_lifeTime > BULLET_EXPLODETIME)
	{
		Move();
		DecreaseLife();
		if (m_lifeTime < BULLET_REDUCTIONSPEEDTIME)
		{
			ReduceSpeed();
			if (m_lifeTime <= m_timeToExplode)
			{
				Explode();
			}
		}
	}
	else
	{
		TimeUp();
	}
}

Explosion* CrossBullet::GetExplosion()
{
	Explosion* explosion = CrossExplosion::create();
	explosion->setPosition(getPosition());
	explosion->setRotation(getRotation());
	Exploded();
	return explosion;
}