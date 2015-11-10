#include "stdafx.h"
#include "Bullet.h"
#include "MoonBullet.h"
#include "MoonExplosion.h"

bool MoonBullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void MoonBullet::Act()
{
}

void MoonBullet::Move()
{
}

Explosion* MoonBullet::GetExplosion() 
{
	return MoonExplosion::create();
}
