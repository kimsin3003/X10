#include "stdafx.h"
#include "Bullet.h"
#include "CrossBullet.h"
#include "Explosion.h"
#include "CrossExplosion.h"

bool CrossBullet::init()
{
	Director* director = Director::getInstance();
	m_screen = director->getVisibleSize();

	m_speed = 0;
	m_direction = Vec2::ZERO;

	m_isFlying = false;
	m_shouldExplode = false;
	m_toBeErased = false;
	m_stopAction = false;

	m_lifeTime = 1.0f;
	m_lifeDecrease = 1.0f / director->getFrameRate();
	m_speedSetRatio = 0.01f;
	m_speedDecreaseRatio = 1 - (10 / BULLET_REDUCTIONSPEEDTIME) / director->getFrameRate();

	m_body = MakeBody();
	addChild(m_body);

	m_pattern = MOVE;
	tmp_BULLET_REDUCTIONSPEEDTIME = m_lifeTime / 10;
	return true;
}

void CrossBullet::Act()
{
	if (m_stopAction)
	{
		return;
	}

	DecreaseLife();
	if (m_lifeTime > BULLET_EXPLODETIME)
	{
		if (m_pattern == MOVE)
			Move();
		
		if (m_lifeTime < tmp_BULLET_REDUCTIONSPEEDTIME)
		{
			ReduceSpeed();
		}
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
			TimeUp();
		}
	}
}

Explosion* CrossBullet::GetExplosion()
{
	Explosion* explosion = CrossExplosion::create();

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