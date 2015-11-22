#include "stdafx.h"
#include "Target.h"
#include "Bullet.h"
#include "SeeBird.h"

bool SeeBird::init()
{
	m_spr = Sprite::create(FILE_SEEBIRD);
	m_feather = Sprite::create(FILE_FEATHER);

	Size winSize = Director::getInstance()->getWinSize();
	
	setAnchorPoint(Vec2(0, 1));
	setPosition(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
	m_spr->setAnchorPoint(Vec2(0, 0));
	m_spr->setPosition(Point::ZERO);

	addChild(m_spr);

	Sequence* act = Sequence::create(
						DelayTime::create(RandomHelper::random_real(3.0f, 9.0f)),
							MoveBy::create(3.0f, Point(-(winSize.width + BIRD_WIDTH), 0)),
							//RemoveSelf::create(),
							NULL);

	runAction(act);
	
	m_applyEffectToMe = true;

	return true;
}

//나중에 벡터에서 삭제될 수 있도록 
//bullet의 toBeErased 값을 조정하는 방향
//CC_CALLBACK_01 을 활용

void SeeBird::ToBullet(Bullet* bullet)
{
	bullet->StopAction();
	bullet->setPosition(getPosition());
	Sequence* act = Sequence::create(
					DelayTime::create(0.5f),
						MoveBy::create(1.0f, Point(-(Director::getInstance()->getWinSize().width), 0)),
							NULL);

	bullet->runAction(act);
}

void SeeBird::ToSelf(const Bullet* bullet) 
{
	stopAllActions();

	Sequence* act = Sequence::create(
						DelayTime::create(0.5f),
							MoveBy::create(1.0f, Point(-(Director::getInstance()->getWinSize().width), 0)),
								NULL);
	runAction(act);
}

void SeeBird::ToSelf(const Explosion* explosion)
{
	removeFromParent();
}