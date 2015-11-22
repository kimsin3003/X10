#include "stdafx.h"
#include "Target.h"
#include "Bullet.h"
#include "SeeBird.h"

bool SeeBird::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_spr = Sprite::create(FILE_SEEBIRD);

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
	
	return true;
}

//나중에 벡터에서 삭제될 수 있도록 
//bullet의 toBeErased 값을 조정하는 방향
//CC_CALLBACK_01 을 활용

void SeeBird::ToBullet(Bullet* bullet)
{
	if (m_applyEffectToBullet)
	{
		m_applyEffectToBullet = false;

		bullet->StopAction();
		bullet->setPosition(getPosition());
		Sequence* act = Sequence::create(
			DelayTime::create(0.5f),
			MoveBy::create(1.0f, Point(-(Director::getInstance()->getWinSize().width), 0)),
			NULL);

		bullet->runAction(act);
	}
}

void SeeBird::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;

		stopAllActions();

		Size winSize = Director::getInstance()->getWinSize();

		Sequence* act = Sequence::create(
			DelayTime::create(0.5f),
			MoveTo::create(1.0f, Point(-BIRD_WIDTH, getPosition().y)),
			NULL);

		runAction(act);

		Sequence* act_00 = Sequence::create(
			DelayTime::create(1.65f),
			MoveBy::create(2.0f, Point(winSize.width / 3, -getPosition().y)),
			NULL);

		m_feather = Sprite::create(FILE_FEATHER);
		addChild(m_feather);

		m_feather->setPosition(0, getPosition().y);
		m_feather->runAction(act_00);
		
	}
}

void SeeBird::ToSelf(const Explosion* explosion)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;
		removeFromParent();
		m_toBeErased = true;
	}
}