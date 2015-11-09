#include "stdafx.h"
#include "Bullet.h"
#include "Sling.h"

//Base Class of All Bullets

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	//temporary initialization for test
	spr = Sprite::create("res/bullet.png");
	this->addChild(spr);
	
	speed = 0;
	direction = Vec2::ZERO;
	timeDecrease = 1;

	//status
	isFlying = false;
	isAlive = true;

	//depending on the type of bullet
	lifeTime = Director::getInstance()->getFrameRate()*1.0;
	speedSetRatio = 0.3;
	speedDecreaseRatio = 0.99;

	return true;
}

void Bullet::Act()
{
	if (lifeTime > 0)
	{
		Move();
		DecreaseLife();

		if (lifeTime < 15)
		{
			SetSpeed(speed * speedDecreaseRatio);
			speedDecreaseRatio -= 0.06;
		}
	}
	else
	{
		removeFromParent();
		isAlive = false;
		isFlying = false;
	}
}

//move bullet 'node', not its sprite
void Bullet::Move()
{
	Vec2 delta = speed * direction;
	Vec2 curPos = this->getPosition();
	setPosition(curPos + delta);
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
