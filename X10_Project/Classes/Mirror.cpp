#include "stdafx.h"
#include "Target.h"
#include "Mirror.h"

bool Mirror::init()
{
	spr = Sprite::create("res/targets/Mirror.png"); //example

	return true;
}

void Mirror::ApplyEffectToBullet(Bullet* bullet)
{

}