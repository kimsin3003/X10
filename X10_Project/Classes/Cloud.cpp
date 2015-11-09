#include "stdafx.h"
#include "Target.h"
#include "Cloud.h"

bool Cloud::init()
{
	spr = Sprite::create("res/targets/Mirror.png"); //example

	return true;
}

void Cloud::ApplyEffectToBullet(Bullet* bullet)
{

}


