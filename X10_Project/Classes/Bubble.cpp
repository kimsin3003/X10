#include "stdafx.h"
#include "Target.h"
#include "Bubble.h"

bool Bubble::init()
{
	spr = Sprite::create("res/targets/Mirror.png"); //example ///# 문자 리터럴

	return true;
}

void Bubble::ApplyEffectToBullet(Bullet* bullet)
{

}


