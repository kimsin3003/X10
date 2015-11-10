#include "stdafx.h"
#include "Bullet.h"

//Base Class of All Bullets

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	speed = 0;
	direction = Vec2::ZERO;
	timeDecrease = 1;

	isBullet = true;
	isFlying = false;
	isExplosing = false;

	//depending on the type of bullet
	lifeTime = Director::getInstance()->getFrameRate()*1.0;
	speedSetRatio = 0.3f;
	speedDecreaseRatio = 0.90f;

	MakeBody();
	addChild(body);

	return true;
}

Sprite* Bullet::MakeBody()
{
	body = Sprite::create();

	float scale = Director::getInstance()->getContentScaleFactor();
	const Size fireSize(BULLET_WIDTH / scale / BULLET_RATIO, BULLET_HEIGHT / scale / BULLET_RATIO); 
	int frameCut = BULLET_FRAMES;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(frameCut);
	
	for (int i = 0; i < frameCut; i++)
	{
		SpriteFrame* frame = SpriteFrame::create("res/firework.png", Rect(Point(fireSize.width*i, 0), fireSize)); 
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
	if (lifeTime > BULLET_EXPLODETIME)
	{
		Move();
		if (lifeTime < BULLET_REDUCTIONSPEEDTIME)
		{
			SetSpeed(speed * speedDecreaseRatio);
			SetSpeedDecreaseRatio(speedDecreaseRatio - 0.05f);
		}
		DecreaseLife();
	}
	else
	{
		removeFromParent();
		SetFlying(false);
		SetExplosing(true);
	}
}

void Bullet::Move()
{
	Vec2 delta = speed * direction;
	Vec2 curPos = getPosition();
	setPosition(curPos + delta);
}

void Bullet::DecreaseLife()
{
	lifeTime -= timeDecrease;
}

///# 함수 안에서 자원을 생성한 다음에 그 포인터를 밖으로 넘겨주는 디자인은 나빠요... 
///자원관리하기 아주 힘들다..
Explosion* Bullet::GetExplosion()
{
	Explosion* explosion = Explosion::create();
	return explosion;
}
