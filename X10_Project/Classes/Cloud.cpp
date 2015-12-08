#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Cloud.h"
#include "FileStuff.h"

bool Cloud::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_isEnemy = false;
	m_spr = Sprite::create(FileStuff::CLOUD);
	addChild(m_spr);

	return true;
}

void Cloud::ToBullet(Bullet* bullet)
{

}

void Cloud::ToSelf(const Bullet* bullet) ///# bullet인자를 쓰지도 않는데, 계속 이렇게 구현하면, 인터페이스가 잘못되었을 확률이 높다.
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;

		m_spr->setVisible(false); 

		Sprite* spr_00 = Sprite::create(FileStuff::CLOUD_LEFT);
		Sprite* spr_01 = Sprite::create(FileStuff::CLOUD_RIGHT);

		addChild(spr_00);
		addChild(spr_01);

		spr_00->setPosition(Vec2(-20, 0));
		spr_01->setPosition(Vec2(20, 0));

		Sequence* action_00 = Sequence::create(
			MoveBy::create(1.0f, Vec2(-30, 0)),
			RemoveSelf::create(),
			NULL);

		Sequence* action_01 = Sequence::create(
			MoveBy::create(1.0f, Vec2(30, 0)),
			RemoveSelf::create(),
			NULL);

		Sequence* action_02 = Sequence::create(
			DelayTime::create(1.25f),
		//	RemoveSelf::create(),
			NULL);

		spr_00->setScale(m_sprScaleRatio);
		spr_01->setScale(m_sprScaleRatio);

		spr_00->runAction(action_00);
		spr_01->runAction(action_01);
	//	m_spr->runAction(action_02);

		m_toBeErased = true;
	}
}

void Cloud::ToSelf(const Explosion* explosion)
{

}

