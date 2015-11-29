#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Star.h"
#include "FileStuff.h"

namespace FileStuff
{
	const string STAR_HAPPY = "res/target/StarSad.png";
	const string STAR_SAD = "res/target/StarHappy.png";
}

bool Star::init()
{
	if (!Target::init())
	{
		return false;
	}
	m_spr = Sprite::create(FileStuff::STAR_SAD);
	addChild(m_spr);
	m_isEnemy = false;
	m_applyEffectToMe = true;
	m_applyEffectToBullet = true;
	return true;
}

void Star::ToBullet(Bullet* bullet)
{
	if (m_applyEffectToBullet)
	{
		bullet->Crashed();
		m_applyEffectToBullet = false;
	}
}

void Star::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		m_spr->removeFromParent();
		m_spr = Sprite::create(FileStuff::STAR_HAPPY);
		addChild(m_spr);
		m_sprScaleRatio *= 2.0f;
		m_spr->setScale(m_sprScaleRatio);

		m_applyEffectToMe = false;
	}
}

void Star::ToSelf(const Explosion* explosion)
{

}
