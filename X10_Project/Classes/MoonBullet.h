#pragma once

#include "Bullet.h"

class MoonBullet : public Bullet
{
public:
	CREATE_FUNC(MoonBullet);
	bool init() override;
	void Act() override;
	void Move() override; // called each frame 
	Explosion* GetExplosion() override;
};