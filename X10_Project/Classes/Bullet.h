#pragma once

class Bullet : public Node
{
public:
	CREATE_FUNC(Bullet);
	virtual bool init() override;
	void Move(); // called each frame 
	void SetDirection(Vec2 dir);
	void SetSpeed(float spd);
	bool IsFlying();
	void SetFlying(bool flag);
	bool IsAlive();
	void SetAlive(bool flag);
private:
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
