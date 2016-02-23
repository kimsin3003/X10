#ifndef EXPLOSION_H 
#define EXPLOSION_H 

#include "Collider.h"

class Explosion : public Collider
{
public:
	CREATE_FUNC(Explosion);
	bool init();

	void Act();
	bool IsBullet() { return false; }
	const float& GetBoundingRadius();

	enum
	{
		DEFAULT_RADIUS = 40
	};

protected:
	void RemoveSelf();

	ParticleExplosion* m_explosion;
	
	float m_lifeTime;
	float m_lifeDecrease;
	float m_radius;
	float m_maxRadius;
};

#endif