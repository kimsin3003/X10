#include "stdafx.h"
#include "Target.h"
#include "Star.h"
#include "FileStuff.h"
#include "Bullet.h"

bool Star::init()
{
	if (!Target::init())
	{
		return false;
	}
	m_spr = Sprite::create(FileStuff::STAR_SAD);
	addChild(m_spr);
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
		m_applyEffectToMe = false;
	}
}

void Star::ToSelf(const Explosion* explosion)
{

}
