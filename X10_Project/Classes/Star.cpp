#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Star.h"

bool Star::init()
{
	spr = Sprite::create(FILE_MIRROR);
	addChild(spr);
	return true;
}

void Star::ToBullet(Bullet* bullet)
{
	Vec2 curDir = bullet->GetDirection();
	Vec2 reflect = Vec2(curDir.x * -1, curDir.y);
	bullet->SetDirection(reflect);
}

void Star::ToExplosion(Explosion* explosion)
{

}

void Star::ToSelf(const Bullet* bullet)
{
	spr->removeFromParent();
	spr = Sprite::create(FILE_MIRROR_ANGRY);
	addChild(spr);
	sprScaleRatio *= 1.05f;
	spr->setScale(sprScaleRatio);
}

void Star::ToSelf(const Explosion* explosion)
{

}
