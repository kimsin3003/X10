#pragma once

#include "Collider.h"
#include "Explosion.h"

class Bullet : public Collider
{
public:
	CREATE_FUNC(Bullet);
	virtual bool init() override;
	virtual void Act() override;
	void Move(); // called each frame 
	bool IsFlying();
	bool IsExplosing();
	virtual Explosion* GetExplosion();

	void SetDirection(Vec2 dir);
	void SetSpeed(float spd);
	void SetExplosing(bool flag);

	void SetFlying(bool flag);
	bool IsAlive() override;
	bool IsBullet() override;
	void SetAlive(bool flag);

protected:
	void DecreaseLife(); // called in Move()

	Sprite* spr;
	Vec2 direction;
	float speed;
	float lifeTime;

	float speedSetRatio;
	float speedDecreaseRatio;
	float timeDecrease;

	//Status - Game manager controls bullet according to its status
	
	bool isFlying; //T - Game manager checks Collision
	bool isAlive; 
private:
	const int DEFAULT_FRAMES = 5;
	const float DEFAULT_WIDTH = 20;
	const float DEFAULT_HEIGHT = 20;
	const float DEFAULT_RATIO = 2;
	bool isExplosing;
};