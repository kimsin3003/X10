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
	m_stopAction = false;
	m_lifeTime = 3.0f;
	m_startLife = m_lifeTime;
	m_lifeDecrease = 1.0 / director->getFrameRate();
	m_speedSetRatio = 0.01f;
	m_speedDecreaseRatio = 1 - (10.0f/BULLET_REDUCTIONSPEEDTIME) / director->getFrameRate();

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


void Bullet::Act()
{
	if (m_stopAction)
	{
		return;
	}

	if (m_lifeTime > BULLET_EXPLODETIME)
	{
		Move();
		DecreaseLife();
		ReduceSpeed();
	}
	else
	{
		Explode();
		TimeUp();
	}
}

void Bullet::SetStartSpeed(float speed)
{
	m_startSpeed = speed * m_speedSetRatio;
	SetSpeed(speed);
}

void Bullet::SetSpeed(float spd)
{
	m_speed = spd * m_speedSetRatio;
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
	explosion->setPosition(getPosition());
	explosion->setRotation(getRotation());
	Exploded();
	return explosion;
}

void Bullet::DecreaseLife()
{
	m_lifeTime -= m_lifeDecrease;
}

void Bullet::ReduceSpeed()
{
	m_speed = (m_lifeTime / m_startLife) * m_startSpeed;
}

void Bullet::Crashed()
{
	m_lifeTime = BULLET_EXPLODETIME;
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