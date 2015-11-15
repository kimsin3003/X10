#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Cloud.h"

bool Cloud::init()
{
	spr = Sprite::create(FILE_CLOUD);
	setPosition(Vec2(200, 200));
	addChild(spr);

	return true;
}

void Cloud::ToBullet(Bullet* collider)
{

}

void Cloud::ToExplosion(Explosion* explosion)
{

}

void Cloud::ToSelf(const Bullet* bullet)
{

}

void Cloud::ToSelf(const Explosion* explosion)
{

}

