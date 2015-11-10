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
	ParticleExplosion* particle; ///# 부모 클래스에도 똑같은 멤버 변수가 있는데??? 이거 잘못하면 엄청난 버그로 돌아올수도 ㅎㅎ
};