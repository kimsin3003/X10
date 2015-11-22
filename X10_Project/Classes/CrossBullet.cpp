#include "stdafx.h"
#include "Bullet.h"
#include "CrossBullet.h"
#include "Explosion.h"
#include "CrossExplosion.h"

bool CrossBullet::init()
{
	Bullet::init();
	return true;
}

void CrossBullet::Act()
{
	DecreaseLife();
	if (m_lifeTime > BULLET_EXPLODETIME)
	{
		Move();
		if (m_lifeTime < BULLET_REDUCTIONSPEEDTIME)
		{
			ReduceSpeed();
		}
	}
	else
	{
		if (m_lifeTime < 0)
		{
			Explode();
		}
		else if (m_lifeTime < -DELTA_TIME)
		{
			Explode();
		}

		TimeUp();
	}
}

Explosion* CrossBullet::GetExplosion()
{
	Explosion* explosion = CrossExplosion::create();
	switch (m_explosion_pattern)
	{
	case CENTER:
		break;
	case CROSS:
		break;
	}
	explosion->SetPosition(getPosition());
	explosion->setRotation(getRotation());
	Exploded();
	return explosion;
}