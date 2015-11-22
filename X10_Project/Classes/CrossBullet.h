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
	int m_pattern;
	int m_crossDir;
	enum 
	{
		CENTER, 
		CROSS_LEFT,
		CROSS_RIGHT,
		CROSS_UP,
		CROSS_DOWN,
		DIE,
		DELTA_POS = 15,
		DELTA_TIME = 60
	};
};