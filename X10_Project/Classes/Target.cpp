#include "stdafx.h"
#include "Target.h"
#include "Explosion.h"
#include "Bullet.h"

//Base class of all Targets

bool Target::init()
{
	spr = Sprite::create("res/angle.png");
	addChild(spr);
	return true;
}

void Target::ApplyCollisionEffect(Collider* collider)
{
	if (collider->IsBullet())
	{
		ToBullet((Bullet*)collider);
		ToSelf((Bullet*)collider);
	}
	else
	{
		ToExplosion((Explosion*)collider);
		ToSelf((Explosion*)collider);
	}
}

void Target::ToBullet(Bullet* bullet)
{

}

void Target::ToExplosion(Explosion* explosion)
{

}

void Target::ToSelf(Bullet* bullet)
{

}

void Target::ToSelf(Explosion* explosion)
{

}