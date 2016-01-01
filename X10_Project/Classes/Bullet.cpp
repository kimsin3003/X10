#include "stdafx.h"
#include "Bullet.h"
#include "FileStuff.h"

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	Director* director = Director::getInstance();
	m_screen = director->getVisibleSize();

	m_speed = 0.0f;
	m_speedSetRatio = 0.01f;
	m_speedDecreaseRatio = 1 - (10.0f / BULLET_REDUCTION_SPEED_TIME) / director->getFrameRate();
	m_direction = Vec2::ZERO;
	
	m_isFlying = false;
	m_isToExplode = false;
	m_toBeErased = false;
	m_isStopped = false;
	m_currentCollidingTarget = nullptr;

	m_lifeTime = BULLET_LIFETIME;
	m_startLife = m_lifeTime;
	m_lifeDecrease = BULLET_LIFE_DECREASE_DELTA / director->getFrameRate();
	
	m_body = MakeBody();
	addChild(m_body);

	m_spr = Sprite::create(FileStuff::NORMAL_BULLET);

	//Add debris to bullet
	CallFunc* addDebris = CallFunc::create(CC_CALLBACK_0(Bullet::AddDebrisToParent, this));
	Sequence* addDelay = Sequence::create(DelayTime::create(0.3f), addDebris, NULL);
	RepeatForever* DebrisEffect = RepeatForever::create(addDelay);
	runAction(DebrisEffect);

	return true;
}

void Bullet::AddDebrisToParent()
{
	if (Node* gameLayer = getParent())
	{
		gameLayer->addChild(MakeDebris());
	}
}

Sprite* Bullet::MakeDebris()
{
	Sprite* debris = Sprite::create(FileStuff::DEBRIS);
	debris->setPosition(this->getPosition());
	MoveBy* fall = MoveBy::create(2.0, Vec2(0, -100));
	auto ease = EaseIn::create(fall, 2.0);
	Sequence* action = Sequence::create(ease, RemoveSelf::create(), NULL);
	debris->runAction(action);
	return debris;
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
		SpriteFrame* frame = SpriteFrame::create(FileStuff::BULLET, Rect(Point(fireSize.width*i, 0), fireSize));
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
	if (m_isStopped)
	{
		return;
	}

	if (m_lifeTime > BULLET_EXPLODE_TIME)
	{
		Move();
		DecreaseLife();
		ReduceSpeed();
	}
	else
	{
		Explode();
		Dead();
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
	explosion->setPosition(getPosition());
	explosion->setRotation(getRotation());
	Exploded();
	return explosion;
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

void Bullet::ReduceSpeed()
{
	m_speed = (m_lifeTime / m_startLife) * m_startSpeed;
}

void Bullet::DecreaseLife()
{
	m_lifeTime -= m_lifeDecrease;
}

void Bullet::Dead()
{
	removeFromParent();
	m_isFlying = false;
	m_toBeErased = true;
}

const Rect& Bullet::GetBoundingArea()
{
	return Rect(this->getPosition(), m_body->getContentSize());
}