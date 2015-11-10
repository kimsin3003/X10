#include "stdafx.h"
#include "Target.h"
#include "Bullet.h"

//Base class of all Targets

bool Target::init()
{
	spr = Sprite::create("res/angle.png");
	addChild(spr);
	return true;
}

void Target::ApplyEffectToBullet(Bullet* bullet)
{

}