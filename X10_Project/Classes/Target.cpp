#include "stdafx.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Target.h"

//Base class of all Targets

bool Target::init()
{
	return true;
}

void Target::ApplyCollisionEffect(Collider* collider)
{
	if (collider->IsBullet())
	{
		ToBullet(static_cast<Bullet*>(collider));
		ToSelf(static_cast<Bullet*>(collider));
	}
	else
	{
		ToExplosion(static_cast<Explosion*>(collider));
		ToSelf(static_cast<Explosion*>(collider));
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