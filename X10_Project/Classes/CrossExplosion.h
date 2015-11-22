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
<<<<<<< HEAD
	void RemoveSelf(ColliderManager* cm);
=======
	enum {lingNum = 5, lingBeginDelta = 20, lingPosDelta = 45};
	void InitLings();
	void SetLingDefault(ParticleExplosion* ling);
	void AddLings();
	Vector<ParticleExplosion*> m_crossLings;
	int m_lingBeginTime;
	int m_curLingIdx;

	void RemoveSelf();
>>>>>>> 5a8837018c312adb3dc497428af7a5403fc54f99
};