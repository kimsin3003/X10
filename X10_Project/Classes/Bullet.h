#pragma once

class Bullet : public cocos2d::Node
{
public:
	CREATE_FUNC(Bullet);
	bool init();
	void Move();
	
	void SetDirection(Vec2 dir);
	void SetSpeed(float spd);
	
	bool IsAlive();
	void SetAlive(bool flag);
	bool IsExplosion();
	void SetExplosion(bool flag);
	bool IsFlying();
	void SetFlying(bool flag);

private:
	Sprite* spr;
	float speed;
	Vec2 direction;
	float lifeTime;

	//HELP!!!
	//FSM - more than two flags can be enabled 
	//ex) isAlive = T, isFlying = T
	
	//Status - Game manager controls bullet according to its status
	bool isAlive; //T - ?
	bool isExplosion; //T - Game manager sets bullet dead and loads Explosion Effect 
	bool isFlying; //T - Game manager checks Collision
};
