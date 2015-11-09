#pragma once

#include "Collider.h"
#include "Explosion.h"

class Bullet : public Collider
{
public:
	CREATE_FUNC(Bullet);
	virtual bool init() override;
	virtual void Act() override;
	virtual void Move(); // called each frame 
	virtual bool IsFlying();
	virtual Explosion* GetExPlosion() { return explosion; }

	void SetDirection(Vec2 dir);
	void SetSpeed(float spd);

	void SetFlying(bool flag);
	bool IsAlive() override;
	bool IsBullet() override { return true; }
	void SetAlive(bool flag);

protected:
	void DecreaseLife(); // called in Move()


	Sprite* spr;
	Vec2 direction;
	Explosion* explosion;
	float speed;
	float lifeTime;
	
	float speedSetRatio;
	float speedDecreaseRatio;
	float timeDecrease;

	//Status - Game manager controls bullet according to its status
	bool isFlying; //T - Game manager checks Collision
};