#include "stdafx.h"
#include "Target.h"
#include "SeeBird.h"

bool SeeBird::init()
{
	m_spr = Sprite::create(FILE_SEEBIRD);
	addChild(m_spr);
	m_applyEffectToMe = true;

	return true;
}

void SeeBird::ToBullet(Bullet* collider)
{

}

void SeeBird::ToExplosion(Explosion* explosion)
{

}

void SeeBird::ToSelf(const Bullet* bullet)
{

}

void SeeBird::ToSelf(const Explosion* explosion)
{

}