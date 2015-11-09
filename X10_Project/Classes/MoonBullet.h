#pragma once

#include "Bullet.h"

class MoonBullet : public Bullet
{
public:
	CREATE_FUNC(MoonBullet);
	virtual bool init();
	virtual void Act();
	virtual void Move(); // called each frame 

	virtual bool IsFlying();

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
};