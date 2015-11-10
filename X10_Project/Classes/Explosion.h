#pragma once

#include "Collider.h"

class Explosion : public Collider
{
public:
	///# 기본 생성자에서 멤버 초기화 할 것

	CREATE_FUNC(Explosion);
	virtual bool init();
	virtual void Act();
	virtual bool IsFlying();
	virtual void SetFlying(bool flag);
	bool IsBullet() override;
	void SetPosition(Vec2 position);

protected:
	ParticleExplosion* particle; ///# 코딩 컨벤션
	int lifeTime;
};