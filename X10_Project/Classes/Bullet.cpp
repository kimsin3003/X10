#include "stdafx.h"
#include "Bullet.h"


bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	//temporary initailization for test
	this->setPosition(Vec2(100, 100)); //Bullet manager sets bullet position
	this->addChild(spr);
	spr = Sprite::create("res/bullet.png");

	speed = 0;
	direction = Vec2::ZERO;
	lifeTime = 0;
	decreaseRatio = 0;
	
	//status
	isFlying = false;
	isExplosion = false;

	return true;
}

//move bullet 'node', not its sprite
void Bullet::Move()
{
	Vec2 delta = speed * direction;
	Vec2 curPos = this->getPosition();
	this->setPosition(curPos + delta);

	DecreaseLife();
	
	if (lifeTime < 10)
		SetSpeed(speed - decreaseRatio);
}

//add : as lifeTime gets near to zero, 1. speed decreases 2. color turns red
void Bullet::DecreaseLife()
{
	lifeTime -= decreaseRatio;
}

void Bullet::SetDirection(Vec2 dir)
{	
	direction = dir;	
}

void Bullet::SetSpeed(float spd)
{
	speed = spd;
}

bool Bullet::IsExplosion()
{
	return isExplosion;
}

void Bullet::SetExplosion(bool flag)
{
	isExplosion = flag;
}

bool Bullet::IsFlying()
{
	return isFlying;
}

void Bullet::SetFlying(bool flag)
{
	isFlying = flag;
}
