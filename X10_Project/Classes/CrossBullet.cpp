#include "stdafx.h"
#include "Bullet.h"
#include "CrossBullet.h"
#include "Explosion.h"
#include "CrossExplosion.h"
#include "FileStuff.h"

bool CrossBullet::init()
{
	Bullet::init();

	m_spr = Sprite::create(FileStuff::CROSS_BULLET);
	m_pattern = MOVE;

	return true;
}

void CrossBullet::Act()
{
	if (m_isStopped)
	{
		return;
	}

	DecreaseLife();
	if (m_lifeTime > BULLET_EXPLODE_TIME)
	{
		if (m_pattern == MOVE)
		{
			Move();
		}
		
		ReduceSpeed();
	}
	else
	{
		switch (m_pattern)
		{
		case MOVE: 
			m_pattern = CENTER;
		case CENTER:
			Explode();
			m_lifeTime += DELTA_TIME;
			break;
		case CROSS_DOWN: case CROSS_UP: case CROSS_LEFT: case CROSS_RIGHT:
			Explode();
			break;
		case DIE:
			Dead();
		}
	}
}

Explosion* CrossBullet::GetExplosion()
{
	Explosion* explosion = Explosion::create();

	explosion->setRotation(getRotation());

	switch (m_pattern)
	{
	case CENTER:
		explosion->setPosition(getPosition());
		m_pattern = CROSS_DOWN;
		break;
	case CROSS_DOWN:
		explosion->setPosition(getPosition() + Point(0, -DELTA_POS));
		m_pattern = CROSS_UP;
		break;
	case CROSS_UP:
		explosion->setPosition(getPosition() + Point(0, DELTA_POS));
		m_pattern = CROSS_LEFT;
		break;
	case CROSS_LEFT:
		explosion->setPosition(getPosition() + Point(-DELTA_POS, 0));
		m_pattern = CROSS_RIGHT;
		break;
	case CROSS_RIGHT:
		explosion->setPosition(getPosition() + Point(DELTA_POS, 0));
		m_pattern = DIE;
		break;
	}

	Exploded();

	return explosion;
}