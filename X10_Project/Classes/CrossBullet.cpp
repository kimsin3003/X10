#include "stdafx.h"
#include "CrossBullet.h"
#include "ColliderManager.h"
#include "GameManager.h"
#include "Explosion.h"
#include "CrossExplosion.h"
#include "Bullet.h"

bool CrossBullet::init()
{
	if (!Bullet::init())
	{
		return false;
	}
	
	m_timeToExplode = 140;
	

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
			if (m_lifeTime <= m_timeToExplode)
			{
				Explode();
				m_timeToExplode = STOP_COUNTING_EXPLODE_TIME;
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
	explosion->setPosition(getPosition());
	explosion->setRotation(getRotation());
	Exploded();
	return explosion;
}