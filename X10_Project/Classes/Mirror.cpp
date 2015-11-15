#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Mirror.h"

bool Mirror::init()
{
	spr = Sprite::create(FILE_MIRROR);
	addChild(spr);
	return true;
}

void Mirror::ToBullet(Bullet* bullet)
{
	Vec2 curDir = bullet->GetDirection();
	Vec2 reflect = Vec2(curDir.x * -1, curDir.y);
	bullet->SetDirection(reflect);
}

void Mirror::ToExplosion(Explosion* explosion)
{

}

void Mirror::ToSelf(const Bullet* bullet)
{
	spr->removeFromParent();
	spr = Sprite::create(FILE_MIRROR_ANGRY);
	addChild(spr);
	sprScaleRatio *= 1.05f;
	spr->setScale(sprScaleRatio);
}

void Mirror::ToSelf(const Explosion* explosion)
{

}
