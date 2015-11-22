#include "stdafx.h"
#include "Bullet.h"
#include "Explosion.h"

//Base Class of All Bullets

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	Director* director = Director::getInstance();
	m_screen = director->getVisibleSize();

	m_speed = 0;
	m_direction = Vec2::ZERO;
	
	m_isFlying = false;
	m_shouldExplode = false;
	m_toBeErased = false;

	m_lifeTime = 5.0;
	m_timeDecrease = 1.0 / director->getFrameRate();
	m_speedSetRatio = 0.01f;
	m_speedDecreaseRatio = 1 - (10/BULLET_REDUCTIONSPEEDTIME) / director->getFrameRate();

	m_body = MakeBody();
	addChild(m_body);

	return true;
}

Sprite* Bullet::MakeBody()
{
	Sprite* body = Sprite::create();

	float scale = Director::getInstance()->getContentScaleFactor();
	Size fireSize(BULLET_WIDTH /scale , BULLET_HEIGHT /scale); 
	int frameCut = BULLET_FRAMES;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(frameCut);
	for (int i = 0; i < frameCut; i++)
	{
		SpriteFrame* frame = SpriteFrame::create(FILE_NAME, Rect(Point(fireSize.width*i, 0), fireSize));
		animFrames.pushBack(frame);
	}
	
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	RepeatForever *aniAction = RepeatForever::create(animate);
	body->runAction(aniAction);
	body->setScale(BULLET_RATIO);
	return body;
}

bool Bullet::NotShooted()
{
	CCLOG("m_lifeTime: %d", m_lifeTime);
	
	if (m_shouldExplode)
		CCLOG("ex: true");
	else
		CCLOG("ex: false");
	
	if (m_lifeTime > 0 && !m_isFlying)
		return true;

	return false;
}

void Bullet::Act()
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
		Explode();
		TimeUp();
	}
}

void Bullet::Move()
{
	const Vec2 delta = m_speed * m_direction;
	const Vec2 curPos = getPosition();
	Vec2 newPos;
	if (curPos.x + delta.x < 0)
	{
		newPos = Vec2(curPos.x + delta.x + m_screen.width, delta.y + curPos.y);
	}
	else if (curPos.x + delta.x > m_screen.width)
	{
		newPos = Vec2(curPos.x + delta.x - m_screen.width, delta.y + curPos.y);
	}
	else
	{
		newPos = curPos + delta;
	}
	setPosition(newPos);
}

Explosion* Bullet::GetExplosion()
{
	Explosion* explosion = Explosion::create();
	explosion->SetPosition(getPosition());
	explosion->setRotation(getRotation());
	Exploded();
	return explosion;
}

void Bullet::DecreaseLife()
{
	m_lifeTime -= m_timeDecrease;
}

void Bullet::ReduceSpeed()
{
	m_speed *= m_speedDecreaseRatio;
}

void Bullet::Crashed()
{
	m_lifeTime = -1;
}

void Bullet::TimeUp()
{
	removeFromParent();
	m_isFlying = false;
	m_toBeErased = true;
}

const Rect& Bullet::GetBoundingArea()
{
	return Rect(this->getPosition(), m_body->getContentSize()*BULLET_RATIO);
}