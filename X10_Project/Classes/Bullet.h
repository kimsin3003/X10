#pragma once

#include "Collider.h"
#include "Explosion.h"

class Bullet : public Collider
{
public:
	CREATE_FUNC(Bullet);

	virtual bool init();
	virtual void Act();
	virtual Explosion* GetExplosion();
	void Move();

	void SetDirection(Vec2 dir) { m_direction = dir; }
	Vec2 GetDirection() { return m_direction; }
	void SetSpeed(float spd) { m_speed = spd * m_speedSetRatio; }
	void SetSpeedDecreaseRatio(float ratio) { m_speedDecreaseRatio = ratio; }
	const Rect& GetBoundingArea();
	
	bool IsBullet() { return true; }
	bool ShouldExplode() { return m_shouldExplode; }

	void Crashed();
	void Explode() { m_shouldExplode = true; }
	void Exploded() { m_shouldExplode = false; }
	void TimeUp();
	void ReduceSpeed();
	bool NotShooted();

protected:
	void DecreaseLife();
	Sprite* MakeBody();
	Sprite* m_body;

	Vec2 m_direction;
	float m_speed;
	float m_lifeTime;
	float m_timeDecrease;
	float m_speedSetRatio;
	float m_speedDecreaseRatio;

	bool m_shouldExplode;

	const char* FILE_NAME= "res/firework.png";

	Size m_screen;

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
};