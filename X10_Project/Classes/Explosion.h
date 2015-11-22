#pragma once

#include "Collider.h"
class ColliderManager;

class Explosion : public Collider
{
public:
	CREATE_FUNC(Explosion);
	virtual bool init();
	virtual void Act(ColliderManager* cm);
	const float& GetBoundingRadius();

	void SetFlying(bool flag);
	bool IsBullet() { return false; }
	void SetPosition(Point pos);
protected:
	virtual void RemoveSelf(ColliderManager* cm);
	ParticleExplosion* m_explosion;
	float m_lifeTime;
	float m_radius;
	float m_maxRadius;
};