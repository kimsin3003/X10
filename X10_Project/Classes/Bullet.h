#pragma once

class Bullet : public Node
{
public:
	CREATE_FUNC(Bullet);
	bool init();
	void Move(); // called each frame 
	void DecreaseLife(); // called in Move()
	void SetDirection(Vec2 dir);
	void SetSpeed(float spd);
	
	bool IsExplosion();
	void SetExplosion(bool flag);
	bool IsFlying();
	void SetFlying(bool flag);

private:
	Sprite* spr;
	Vec2 direction;
	float speed;
	float lifeTime;
	float decreaseRatio;

	//Status - Game manager controls bullet according to its status
	bool isFlying; //T - Game manager checks Collision
	bool isExplosion; //T - Game manager removes bullet and loads Explosion Effect 
};
