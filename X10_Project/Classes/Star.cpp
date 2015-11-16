#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Star.h"

bool Star::init()
{
	spr = Sprite::create(FILE_STAR_SAD);
	addChild(spr);
	ApplyEffectToMe = true;
	ApplyEffectToBullet = true;
	return true;
}

void Star::ToBullet(Bullet* bullet)
{
	if (ApplyEffectToBullet)
	{
		bullet->Crashed();
		ApplyEffectToBullet = false;
	}
}

void Star::ToExplosion(Explosion* explosion)
{

}

void Star::ToSelf(const Bullet* bullet)
{
	if (ApplyEffectToMe)
	{
		spr->removeFromParent();
		spr = Sprite::create(FILE_STAR_HAPPY);
		addChild(spr);
		sprScaleRatio *= 2.0f;
		spr->setScale(sprScaleRatio);

		ApplyEffectToMe = false;
	}
}

void Star::ToSelf(const Explosion* explosion)
{

}
