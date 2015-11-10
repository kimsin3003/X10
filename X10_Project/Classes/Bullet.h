#pragma once

#include "Collider.h"
#include "Explosion.h"

class Bullet : public Collider
{
public:
	///# 나중에 따로 init을 부르더라도 기본 생성자에서 멤버 초기화는 반드시 하도록. 
	///# 나중에 초기화가 되기 전에 죽었을때 그걸 확인할 길이 없기 때문...

	CREATE_FUNC(Bullet);

	virtual bool init() override;
	virtual void Act() override;
	virtual void Move();
	virtual Explosion* GetExplosion();

	void SetDirection(Vec2 dir);
	void SetSpeed(float spd);

	void SetFlying(bool flag);
	void SetAlive(bool flag);
	void SetExplosing(bool flag);
	bool IsExplosing();
	bool IsFlying();
	bool IsBullet() override;
	bool IsAlive() override;

protected:
	void DecreaseLife(); // called in Move()
	Sprite* MakeBody();

	//Information to give Bullet
	Vec2 direction;
	float speed;
	
	//Variables affecting bullet status 
	float lifeTime;
	float timeDecrease;
	float speedSetRatio;
	float speedDecreaseRatio;

	//Bullet status
	bool isExplosing;

	enum
	{
		BULLET_FRAMES = 5,
		BULLET_WIDTH = 20,
		BULLET_HEIGHT = 20,
		BULLET_RATIO = 2
	};
};