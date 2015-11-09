#pragma once
#include "stdafx.h"

class Bullet;

class Target : public Node
{
public:
	CREATE_FUNC(Target);
	bool init();
	virtual void ApplyEffectToBullet(Bullet* bullet);

private:
	Sprite* spr;
};