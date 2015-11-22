#pragma once

#include "Collider.h"

class Explosion : public Collider
{
public:
	CREATE_FUNC(Explosion);
	virtual bool init();
	virtual void Act();
	const float& GetBoundingRadius();
	void SetPosition(Point pos);
	bool IsBullet() { return false; }

protected:
	void RemoveSelf();
	ParticleExplosion* m_explosion;
	float m_lifeTime;
	float m_radius;
	float m_maxRadius;
};