#include "stdafx.h"
#include "Target.h"
#include "Bubble.h"
#include "FileStuff.h"

namespace FileStuff
{
	const string BUBBLE = "res/target/Bubble2.png";
	const string BUBBLE_POP = "res/target/BubblePop.png";
}

bool Bubble::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_isEnemy = false;
	m_spr = Sprite::create(FileStuff::BUBBLE);
	addChild(m_spr);

	return true;
}

void Bubble::ToBullet(Bullet* bullet)
{

}

void Bubble::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;

		m_spr->removeFromParent();
		m_spr = Sprite::create(FileStuff::BUBBLE_POP);
		m_spr->setScale(m_sprScaleRatio);
		addChild(m_spr);

		Sequence* action = Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create(CC_CALLBACK_0(Bubble::EraseOn, this)),
			NULL);

		m_spr->runAction(action);
	}
}

void Bubble::ToSelf(const Explosion* explosion)
{
	ToSelf(static_cast<Bullet*>(NULL));
}