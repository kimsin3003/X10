#include "stdafx.h"
#include "CrossBullet.h"
#include "ColliderManager.h"
#include "GameManager.h"
#include "Explosion.h"
#include "CrossExplosion.h"
#include "Bullet.h"
//Base Class of All Bullets

bool CrossBullet::init()
{
	if (!Node::init())
	{
		return false;
	}
	Director* director = Director::getInstance();
	m_screen = director->getVisibleSize();

	m_speed = 0;
	m_direction = Vec2::ZERO;
	
	m_isBullet = true;
	m_isFlying = false;
	m_shouldExplode = false;

	//depending on the type of CrossBullet
	m_lifeTime = 5.0;
	m_timeDecrease = 1.0 / director->getFrameRate();
	m_speedSetRatio = 0.01f;
	m_speedDecreaseRatio = 1 - (10/BULLET_REDUCTIONSPEEDTIME) / director->getFrameRate();

	m_body = MakeBody();
	addChild(m_body);

	return true;
}

void CrossBullet::Act(ColliderManager* cm)
{
	if (m_lifeTime > BULLET_EXPLODETIME)
	{
		Move();
		DecreaseLife();
		if (m_lifeTime < BULLET_REDUCTIONSPEEDTIME)
		{
			ReduceSpeed();
			if (m_lifeTime == TimeToExplode)
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

void CrossBullet::Move()
{
	Vec2 delta = m_speed * m_direction;
	Vec2 curPos = getPosition();
	//화면 밖으로 나갈 경우 반대 방향에서 나오게 처리.
	if (curPos.x + delta.x < 0)
	{
		curPos = Vec2(curPos.x + delta.x + m_screen.width, delta.y + curPos.y);
	}
	else if (curPos.x + delta.x > m_screen.width)
	{
		curPos = Vec2(curPos.x + delta.x - m_screen.width, delta.y + curPos.y);
	}
	else
	{
		curPos = curPos + delta;
	}
	setPosition(curPos);
}

Explosion* CrossBullet::GetExplosion()
{
	Explosion* explosion = CrossExplosion::create();
	explosion->setPosition(getPosition()); //test용 , S로 변경
	explosion->setRotation(getRotation());
	Exploded();
	return explosion;
}