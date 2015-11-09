#include "stdafx.h"
#include "Bullet.h"

//Base Class of All Bullets

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	//temporary initialization for test
	Sprite* aniSprite = Sprite::create();
	//애니매이션 프레임 추가
	Vector<SpriteFrame*> animFrames;
	float scale = Director::getInstance()->getContentScaleFactor();
	const Size fireSize(DEFAULT_WIDTH/scale/DEFAULT_RATIO, DEFAULT_HEIGHT/scale/DEFAULT_RATIO);
	int frameCut = DEFAULT_FRAMES;
	animFrames.reserve(frameCut);
	for (int i = 0; i < frameCut; i++){
		SpriteFrame* frame = SpriteFrame::create("res/firework.png", Rect(Point(fireSize.width*i,0), fireSize));
		animFrames.pushBack(frame);
	}
	// create the animation out of the frame
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	RepeatForever *aniAction = RepeatForever::create(animate); //액션을 만들어서
	aniSprite->runAction(aniAction); //스프라이트(spr)에 실행
	aniSprite->setScale(DEFAULT_RATIO);
	this->addChild(aniSprite);

	speed = 0;
	direction = Vec2::ZERO;
	timeDecrease = 1;

	//status
	isExplosing = false;
	isFlying = false;
	isAlive = true;
	//depending on the type of bullet
	lifeTime = Director::getInstance()->getFrameRate()*1.0;
	speedSetRatio = 0.3f;
	speedDecreaseRatio = 0.99f;

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
			speedDecreaseRatio -= 0.06f;
		}
	}
	else
	{
		removeFromParent();
		isAlive = false;
		isFlying = false;
		isExplosing = true;
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

bool Bullet::IsExplosing()
{
	return isExplosing;
}

bool Bullet::IsAlive()
{
	return isAlive;
}

bool Bullet::IsBullet()
{
	return true;
}

Explosion* Bullet::GetExplosion()
{
	Explosion* explosion = Explosion::create();
	explosion->setPosition(getPosition());
	return explosion;
}

void Bullet::SetExplosing(bool flag)
{
	isExplosing = flag;
}
