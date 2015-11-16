#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Star.h"

bool Star::init()
{
	m_spr = Sprite::create(FILE_STAR_SAD);
	addChild(m_spr);
	m_ApplyEffectToMe = true;
	m_ApplyEffectToBullet = true;
	return true;
}

void Star::ToBullet(Bullet* bullet)
{
	if (m_ApplyEffectToBullet)
	{
		bullet->Crashed();
		m_ApplyEffectToBullet = false;
	}
}

void Star::ToExplosion(Explosion* explosion)
{

}

void Star::ToSelf(const Bullet* bullet)
{
	if (m_ApplyEffectToMe)
	{
		m_spr->removeFromParent();
		m_spr = Sprite::create(FILE_STAR_HAPPY);
		addChild(m_spr);
		m_sprScaleRatio *= 2.0f;
		m_spr->setScale(m_sprScaleRatio);

		m_ApplyEffectToMe = false;
	}
}

void Star::ToSelf(const Explosion* explosion)
{

}
