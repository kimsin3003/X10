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

	m_lifeTime = 1.75f;
	m_timeDecrease = 1.0f / director->getFrameRate();
	m_speedSetRatio = 0.01f;
	m_speedDecreaseRatio = 1 - (10 / BULLET_REDUCTIONSPEEDTIME) / director->getFrameRate();

	m_body = MakeBody();
	addChild(m_body);

	m_pattern = CENTER;

	return true;
}

void CrossBullet::Act()
{
	DecreaseLife();
	if (m_lifeTime > BULLET_EXPLODETIME && m_pattern == CENTER)
	{
		Move();
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