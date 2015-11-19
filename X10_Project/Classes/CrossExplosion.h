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
	enum {lingNum = 5, lingBeginDelta = 20, lingPosDelta = 45};
	void InitLings();
	void SetLingDefault(ParticleExplosion* ling);
	void AddLings();
	Vector<ParticleExplosion*> m_crossLings;
	int m_lingBeginTime;
	int m_curLingIdx;
};