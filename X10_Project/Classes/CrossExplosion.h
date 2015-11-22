#pragma once

class ColliderManager;

class CrossExplosion : public Explosion
{
public:
	CREATE_FUNC(CrossExplosion);
	bool init();
	void Act();
	const float& GetBoundingRadius();

private:

};