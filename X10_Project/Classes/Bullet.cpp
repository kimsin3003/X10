#include "stdafx.h"
#include "Bullet.h"


bool Bullet::init()
{
	this->addChild(spr);
}

void Bullet::Move()
{
	Vec2 delta = speed * direction;
	Vec2 curPos = this->getPosition();
	this->setPosition(curPos + delta);
}

void Bullet::SetDirection(Vec2 dir)
{	
	direction = dir;	
}

void Bullet::SetSpeed(float spd)
{
	speed = spd;
}

bool Bullet::IsAlive()
{
	return isAlive;
}

void Bullet::SetAlive(bool flag)
{
	isAlive = flag;
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
