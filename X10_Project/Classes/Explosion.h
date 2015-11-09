#pragma once

#include "Collider.h"

class Explosion : public Collider
{
public:
	CREATE_FUNC(Explosion);
	virtual bool init();
	virtual void Act();
	virtual bool IsFlying();
	virtual void SetFlying(bool flag);
	virtual bool IsAlive() override;
	bool IsBullet() override;
	void SetPosition(Vec2 position);

protected:
	ParticleExplosion* particle;
	int lifeTime;
};