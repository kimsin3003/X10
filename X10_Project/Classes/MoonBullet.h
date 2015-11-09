#pragma once

#include "Bullet.h"

class MoonBullet : public Bullet
{
public:
	CREATE_FUNC(MoonBullet);
	virtual bool init();
	virtual void Act();
	virtual void Move(); // called each frame 
	virtual Explosion* GetExplosion() override;
};