#pragma once

#include "Bullet.h"

class CrossBullet : public Bullet
{
public:
	CREATE_FUNC(CrossBullet);
	bool init();
	void Act();
	Explosion* GetExplosion();

private:
	int m_explosion_pattern;
	enum 
	{
		DELTA_POS = 15,
		DELTA_TIME = 60,
		CENTER, 
		CROSS
	};
};