#include "stdafx.h"
#include "Bullet.h"
#include "MoonBullet.h"

bool MoonBullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	//temporary initialization for test
	spr = Sprite::create("res/Bullet.png");
	this->addChild(spr);

	speed = 0;
	direction = Vec2::ZERO;
	timeDecrease = 1;

	//status
	isFlying = false;
	isAlive = true;

	//depending on the type of MoonBullet
	lifeTime = Director::getInstance()->getFrameRate()*1.0;
	speedSetRatio = 0.3f;
	speedDecreaseRatio = 0.99f;

	return true;
}

void MoonBullet::Act()
{
	if (lifeTime > 0)
	{
		Move();
		DecreaseLife();

		if (lifeTime < 15)
		{
			SetSpeed(speed * speedDecreaseRatio);
			speedDecreaseRatio -= 0.06f;
		}
	}
	else
	{
		removeFromParent();
		isAlive = false;
		isFlying = false;
	}
}

//move MoonBullet 'node', not its sprite
void MoonBullet::Move()
{
	Vec2 delta = speed * direction;
	Vec2 curPos = this->getPosition();
	setPosition(curPos + delta);
}

//add : as lifeTime gets near to zero, 1. speed decreases 2. color turns red
void MoonBullet::DecreaseLife()
{
	lifeTime -= timeDecrease;
}

bool MoonBullet::IsFlying()
{
	return isFlying;
}