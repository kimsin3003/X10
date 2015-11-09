#pragma once

#include "Explosion.h"

class MoonExplosion : public Explosion
{
public:
	CREATE_FUNC(MoonExplosion);
	virtual bool init();
	virtual void Act();
	virtual bool IsFlying();
	virtual void SetFlying(bool flag);

protected:
	ParticleExplosion* particle;
	bool isFlying;
};