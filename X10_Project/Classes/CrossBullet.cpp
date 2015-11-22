#include "stdafx.h"
#include "Bullet.h"
#include "CrossBullet.h"
#include "Explosion.h"
#include "CrossExplosion.h"

bool CrossBullet::init()
{
	Bullet::init();
	m_pattern = CENTER;
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
		}
	}
	else
	{
		switch (m_pattern)
		{
		case CENTER:
			Explode();
			m_lifeTime += DELTA_TIME;
			break;
		case CROSS_DOWN: case CROSS_UP: case CROSS_LEFT: case CROSS_RIGHT:
			Explode();
			break;
		case DIE:
			TimeUp();
		}
	}
}

Explosion* CrossBullet::GetExplosion()
{
	Explosion* explosion = CrossExplosion::create();
	switch (m_pattern)
	{
	case CENTER:
		explosion->SetPosition(getPosition());
		m_pattern = CROSS_DOWN;
		break;
	case CROSS_DOWN:
		explosion->SetPosition(getPosition() + Point(0, -DELTA_POS));
		m_pattern = CROSS_UP;
		break;
	case CROSS_UP:
		explosion->SetPosition(getPosition() + Point(0, DELTA_POS));
		m_pattern = CROSS_LEFT;
		break;
	case CROSS_LEFT:
		explosion->SetPosition(getPosition() + Point(-DELTA_POS, 0));
		m_pattern = CROSS_RIGHT;
		break;
	case CROSS_RIGHT:
		explosion->SetPosition(getPosition() + Point(DELTA_POS, 0));
		m_pattern = DIE;
		break;
	}

	explosion->setRotation(getRotation());
	Exploded();
	return explosion;
}