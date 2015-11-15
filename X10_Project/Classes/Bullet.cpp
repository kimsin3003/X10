#include "stdafx.h"
#include "Bullet.h"
#include "ColliderManager.h"
#include "GameManager.h"

//Base Class of All Bullets

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}
	screen = Director::getInstance()->getVisibleSize();

	speed = 0;
	direction = Vec2::ZERO;
	timeDecrease = 1;

	isBullet = true;
	isFlying = false;
	shouldExplode = false;

	//depending on the type of bullet
	lifeTime = Director::getInstance()->getFrameRate()*1.0;
	speedSetRatio = 0.01f;
	speedDecreaseRatio = 0.90f;

	body = MakeBody();
	addChild(body);

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

void Bullet::Act(ColliderManager* cm)
{
	if (lifeTime > BULLET_EXPLODETIME)
	{
		Move();
		DecreaseLife();
		if (lifeTime < BULLET_REDUCTIONSPEEDTIME)
		{
			ReduceSpeed();
		}
	}
	else
	{
		TimeUp();
	}
}

void Bullet::Move()
{
	Vec2 delta = speed * direction;
	Vec2 curPos = getPosition();
	//화면 밖으로 나갈 경우 반대 방향에서 나오게 처리.
	//if (curPos.x + delta.x < screen.width)
	//{
	//	setPosition(curPos.x + delta.x + screen.width, delta.y + curPos.y);
	//	return;
	//}
	//else if (curPos.x + delta.x > screen.width)
	//{
	//	setPosition(curPos.x + delta.x - screen.width, delta.y + curPos.y);
	//	return;
	//}
	
	setPosition(delta + curPos);
}

Explosion* Bullet::GetExplosion()
{
	Explosion* explosion = Explosion::create();
	explosion->SetPosition(getPosition());
	Exploded();
	return explosion;
}

void Bullet::DecreaseLife()
{
	lifeTime -= timeDecrease;
}

void Bullet::ReduceSpeed()
{
	SetSpeed(speed * speedDecreaseRatio);
	SetSpeedDecreaseRatio(speedDecreaseRatio - 0.05f);
}

void Bullet::Exploded()
{
	shouldExplode = false;
}

//외부에서 bullet을 강제로 죽일 때 사용.(폭발로 이어짐)
void Bullet::Crashed()
{
	lifeTime = 0;
}

void Bullet::TimeUp()
{
	removeFromParent();
	shouldExplode = true;
	isFlying = false;
}

const Rect& Bullet::GetBoundingArea()
{
	return Rect(this->getPosition(), body->getContentSize()*BULLET_RATIO);
}
