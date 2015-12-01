#include "stdafx.h"
#include "Target.h"
#include "Bullet.h"
#include "SeeBird.h"
#include "FileStuff.h"


bool SeeBird::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_isEnemy = false; 
	m_spr = Sprite::create(FileStuff::SEEBIRD);

	Size winSize = Director::getInstance()->getWinSize();
	
	setAnchorPoint(Vec2(0, 1));
	setPosition(winSize.width, RandomHelper::random_real(200.0f, winSize.height));
	m_spr->setAnchorPoint(Vec2(0, 0));
	m_spr->setPosition(Point::ZERO);

	addChild(m_spr);

	Sequence* act = Sequence::create(
						DelayTime::create(RandomHelper::random_real(3.0f, 9.0f)),
							MoveBy::create(3.0f, Point(-(winSize.width + BIRD_WIDTH*3), 0)),
							//RemoveSelf::create(),
							NULL);

	runAction(act);
	
	return true;
}

void SeeBird::ToBullet(Bullet* bullet)
{
	if (m_applyEffectToBullet)
	{
		m_applyEffectToBullet = false;

		Size winSize = Director::getInstance()->getWinSize();

		bullet->StopAction();

		bullet->setPosition(getPosition());
		
		Sequence* act = Sequence::create(
			DelayTime::create(0.5f),
			MoveBy::create(1.0f, Point(-winSize.width - 10, 0)),
			CallFunc::create(CC_CALLBACK_0(Bullet::EraseMe, bullet)),
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
			MoveBy::create(1.0f, Point(-winSize.width - BIRD_WIDTH * 2, 0)),
			NULL);

		m_spr->runAction(act);

		Sequence* act_00 = Sequence::create(
			DelayTime::create(2.00f),
			MoveBy::create(2.0f, Point(winSize.width / 2 + 100, -(getPosition().y))),
			DelayTime::create(2.5f),
			CallFunc::create(CC_CALLBACK_0(SeeBird::EraseOn, this)),
			RemoveSelf::create(),
			NULL);

		m_feather = Sprite::create(FileStuff::FEATHER);
		addChild(m_feather);

		m_feather->setPosition(-(getPosition().x+50), 0);
		m_feather->runAction(act_00);
	}
}

void SeeBird::ToSelf(const Explosion* explosion)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;
		m_applyEffectToBullet = false;
		removeFromParent();
		m_toBeErased = true;
	}
}