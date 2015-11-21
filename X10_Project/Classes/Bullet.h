#pragma once

#include "Collider.h"
class Explosion;
class ColliderManager;

class Bullet : public Collider
{
public:
	CREATE_FUNC(Bullet);

	virtual bool init();
	virtual void Act(ColliderManager* cm);
	virtual void Move();
	virtual Explosion* GetExplosion();

	//Setters and Getters
	void SetDirection(Vec2 dir) { m_direction = dir; }
	Vec2 GetDirection() { return m_direction; }
	const Rect& GetBoundingArea();
	void SetSpeed(float spd) { m_speed = spd * m_speedSetRatio; }
	void SetSpeedDecreaseRatio(float ratio) { m_speedDecreaseRatio = ratio; }
	void SetFlying(bool flag) { m_isFlying = flag; }
	bool IsBullet() { return true; }
	bool IsFlying() { return m_isFlying; }
	bool ShouldExplode() { return m_shouldExplode; }

	//상태 변화
	void Crashed();
	void Explode();
	void Exploded();
	void TimeUp();
	void ReduceSpeed();
	bool ToBeErased() override;
	bool NotShooted();

protected:
	void DecreaseLife(); // call in Move()
	Sprite* MakeBody();

	Sprite* m_body;//임시로 퍼블릭으로 옮김

	Vec2 m_direction;
	float m_speed;
	
	float m_lifeTime;
	float m_timeDecrease;
	float m_speedSetRatio;
	float m_speedDecreaseRatio;

	bool m_shouldExplode;

	const char* FILE_NAME= "res/firework.png";

	enum
	{
		BULLET_FRAMES = 5,
		BULLET_WIDTH = 10,
		BULLET_HEIGHT = 10,
		BULLET_RATIO = 1,

		BULLET_LIFETIME = 30,
		BULLET_EXPLODETIME = 0,
		BULLET_REDUCTIONSPEEDTIME = 3,
	};

	Size m_screen;
};