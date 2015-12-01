#pragma once

#include "Collider.h"

class Explosion : public Collider
{
public:
	CREATE_FUNC(Explosion);
	virtual bool init();

	void Act();
	bool IsBullet() { return false; }
	const float& GetBoundingRadius();

protected:
	Explosion();
	virtual ~Explosion();
	void RemoveSelf();

	ParticleExplosion* m_explosion;
	
	float m_lifeTime;
	float m_lifeDecrease;
	float m_radius;
	float m_maxRadius;

	enum
	{
		DEFAULT_RADIUS = 30
	};
};