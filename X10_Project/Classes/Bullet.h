#pragma once

class Bullet : public cocos2d::Node
{
public:
	CREATE_FUNC(Bullet);
	bool init();
	void SetDirection(Vec2 dir);
	void SetSpeed(float spd);
	void Move();

private:
	Sprite* spr;
	float speed;
	Vec2 direction;
	float lifeTime;
	bool isAlive;
	bool isExplosion;
	bool isFlying;
};
