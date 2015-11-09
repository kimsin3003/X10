#pragma once
#include "Collider.h"

class Explosion : public Collider
{
public:
	CREATE_FUNC(Explosion);
	bool init();
	void Act();
	bool IsFlying();
	void SetFlying(bool flag);
private:
	ParticleExplosion* particle;
	bool isFlying;

};