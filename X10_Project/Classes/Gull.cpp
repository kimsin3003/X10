#include "stdafx.h"
#include "Target.h"
#include "Gull.h"
#include "FileStuff.h"
#include "Bullet.h"

bool Gull::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_spr = Sprite::create(FileStuff::GULL);

	Size winSize = Director::getInstance()->getWinSize();
	
	m_spr->setPosition(Point::ZERO);

	addChild(m_spr);
	
	Sequence* act = Sequence::create(
		DelayTime::create(RandomHelper::random_real(3.0f, 6.0f)),
							MoveBy::create(3.0f, Point(-1000, 0)),
							CallFunc::create(CC_CALLBACK_0(Gull::Respawn, this)),
							NULL);

	runAction(act);
	
	return true;
}

void Gull::ToBullet(Bullet* bullet)
{
	if (m_applyEffectToBullet)
	{
		m_applyEffectToBullet = false;

		Size winSize = Director::getInstance()->getWinSize();

		bullet->StopAction();

		bullet->setPosition(Vec2::ZERO);
		
		Sequence* act = Sequence::create(
			DelayTime::create(0.5f),
			MoveBy::create(3.0f, Point(-1000, 0)),
			CallFunc::create(CC_CALLBACK_0(Bullet::EraseMe, bullet)),
			NULL);

		bullet->runAction(act);
	}
}

void Gull::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;

		stopAllActions();

		Size winSize = Director::getInstance()->getWinSize();

		Sequence* act = Sequence::create(
			DelayTime::create(0.5f),
			MoveBy::create(2.0f, Point(-1000, 0)),
			CallFunc::create(CC_CALLBACK_0(Gull::Respawn, this)),
			NULL);

		m_spr->runAction(act);

		//Sequence* act_00 = Sequence::create(
		//	DelayTime::create(2.00f),
		//	MoveBy::create(2.0f, Point(winSize.width / 2 + 100, -(getPosition().y))),
		//	DelayTime::create(2.5f),
		//	CallFunc::create(CC_CALLBACK_0(Gull::EraseOn, this)),
		//	RemoveSelf::create(),
		//	NULL);

		//m_feather = Sprite::create(FileStuff::FEATHER);
		//addChild(m_feather);

		//m_feather->setPosition(-(getPosition().x+50), 0);
		//m_feather->runAction(act_00);
	}
}

void Gull::ToSelf(const Explosion* explosion)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;
		m_applyEffectToBullet = false;
		removeFromParent();
		
		init();
	}
}

void Gull::Respawn()
{
	Size winSize = Director::getInstance()->getWinSize();

	setPosition(400, getPosition().y);

	Sequence* act = Sequence::create(
		DelayTime::create(3.0f),
		MoveBy::create(3.0f, Point(-1000, 0)),
		CallFunc::create(CC_CALLBACK_0(Gull::Respawn, this)),
		NULL);

	runAction(act);
}
