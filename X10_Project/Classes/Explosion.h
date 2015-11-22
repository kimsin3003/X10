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
	bool ToBeErased() override;

protected:
<<<<<<< HEAD
	virtual void RemoveSelf(ColliderManager* cm);
	ParticleExplosion* m_explosion;
=======
	virtual void RemoveSelf();


	ParticleExplosion* m_explosion; ///# 코딩 컨벤션
>>>>>>> 5a8837018c312adb3dc497428af7a5403fc54f99
	float m_lifeTime;
	float m_radius;
	float m_maxRadius;
};