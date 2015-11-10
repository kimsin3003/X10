#include "stdafx.h"
#include "Bullet.h"
#include "MoonBullet.h"
#include "MoonExplosion.h"

bool MoonBullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	//temporary initialization for test
	spr = Sprite::create("res/Bullet.png"); ///# 마찬가지 문자열 리터럴은 빼서 모아놓기
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

Explosion* MoonBullet::GetExplosion() ///# 함수 안에서 자원을 생성한 다음에 그 포인터를 밖으로 넘겨주는 디자인은 나빠요... 자원관리하기 아주 힘들다.. 
{
	return MoonExplosion::create();
}
