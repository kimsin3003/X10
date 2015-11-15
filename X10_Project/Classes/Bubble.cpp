#include "stdafx.h"
#include "Target.h"
#include "Bubble.h"

bool Bubble::init()
{
	return true;
}


void Bubble::ToBullet(Bullet* collider)
{
}

void Bubble::ToExplosion(Explosion* explosion)
{
}

void Bubble::ToSelf(const Bullet* bullet)
{
}

void Bubble::ToSelf(const Explosion* explosion)
{
}

