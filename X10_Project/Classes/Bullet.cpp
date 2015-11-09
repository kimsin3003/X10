#include "stdafx.h"
#include "Bullet.h"
#include "Sling.h"

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	//temporary initialization for test
	this->setPosition(Sling::GetInstance()->getPosition()); //Game manager sets initial bullet position
	spr = Sprite::create("res/bullet.png");
	this->addChild(spr);
	
	speed = 0;
	direction = Vec2::ZERO;
	lifeTime = 60;
	speedSetRatio = 0.3;
	speedDecreaseRatio = 0.99;
	timeDecrease = 1;

	//status
	isFlying = false;
	isAlive = true;

	return true;
}

//move bullet 'node', not its sprite
void Bullet::Move()
{
	if (lifeTime > 0)
	{
		Vec2 delta = speed * direction;
		Vec2 curPos = this->getPosition();
		this->setPosition(curPos + delta);

		DecreaseLife();

		if (lifeTime < 10)
			SetSpeed(speed * speedSetRatio);
	}
	else
	{
		removeFromParent();
		isAlive = false;
		isFlying = false;
	}
}

//add : as lifeTime gets near to zero, 1. speed decreases 2. color turns red
void Bullet::DecreaseLife()
{
	lifeTime -= timeDecrease;
}

void Bullet::SetDirection(Vec2 dir)
{	
	direction = dir;	
}

void Bullet::SetSpeed(float spd)
{
	speed = spd * speedSetRatio;
}

bool Bullet::IsFlying()
{
	return isFlying;
}

void Bullet::SetFlying(bool flag)
{
	isFlying = flag;
}

bool Bullet::IsAlive()
{
	return isAlive;
}

void Bullet::SetAlive(bool flag)
{
	isAlive = flag;
}

void Bullet::Act()
{
	Move();
}
