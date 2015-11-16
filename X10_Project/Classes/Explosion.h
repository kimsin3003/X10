#pragma once

#include "Collider.h"
#include "ColliderManager.h"

class Explosion : public Collider
{
public:
	CREATE_FUNC(Explosion);
	virtual bool init();
	virtual void Act(ColliderManager* cm);
	virtual const float& GetBoundingRadius();
	virtual void SetFlying(bool flag);

	bool IsBullet() override;
	void SetPosition(Point pos);

protected:
	ParticleExplosion* explosion; ///# 코딩 컨벤션
	int lifeTime;
	float radius;
	float maxRadius;
};