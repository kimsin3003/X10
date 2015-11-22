#include "stdafx.h"
#include "CrossBullet.h"
#include "ColliderManager.h"
#include "GameManager.h"
#include "Explosion.h"
#include "CrossExplosion.h"
#include "Bullet.h"

bool CrossBullet::init()
{
	Director* director = Director::getInstance();
	m_screen = director->getVisibleSize();

	m_speed = 0;
	m_direction = Vec2::ZERO;

	m_isBullet = true;
	m_isFlying = false;
	m_shouldExplode = false;
	m_toBeErased = false;

	m_lifeTime = 5.0;
	m_timeDecrease = 1.0 / director->getFrameRate();
	m_speedSetRatio = 0.01f;
	m_speedDecreaseRatio = 1 - (10 / BULLET_REDUCTIONSPEEDTIME) / director->getFrameRate();

	m_body = MakeBody();
	addChild(m_body);

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