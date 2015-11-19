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
	Vector<ParticleExplosion*> m_crossLings;
	int m_lingBeginTime;
	int m_curLingIdx;
	void AddLings();
	void InitLings();
	void SetLingDefault(ParticleExplosion* ling);
};