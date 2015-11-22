#pragma once

class ColliderManager;

class CrossExplosion : public Explosion
{
public:
	CREATE_FUNC(CrossExplosion);
	bool init();
	void Act(ColliderManager* cm);
	const float& GetBoundingRadius();

private:
	void RemoveSelf(ColliderManager* cm);
};