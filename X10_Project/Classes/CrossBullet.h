#pragma once

#include "Bullet.h"
class Explosion;
class ColliderManager;

class CrossBullet : public Bullet
{
public:
	CREATE_FUNC(CrossBullet);

	bool init();
	void Act(ColliderManager* cm);
	void Move();
	Explosion* GetExplosion();

private:
	float m_timeToExplode;
	enum { STOP_COUNTING_EXPLODE_TIME = -30000};
};