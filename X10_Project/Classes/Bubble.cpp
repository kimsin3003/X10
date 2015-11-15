#include "stdafx.h"
#include "Target.h"
#include "Bubble.h"

bool Bubble::init()
{
	return true;
}


void Bubble::ToBullet(Bullet* collider)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Bubble::ToExplosion(Explosion* explosion)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Bubble::ToSelf(const Bullet* bullet)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Bubble::ToSelf(const Explosion* explosion)
{
	throw std::logic_error("The method or operation is not implemented.");
}

