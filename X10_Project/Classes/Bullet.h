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

	const Rect& GetBoundingArea();

	void SetDirection(const Vec2& dir) { m_direction = dir; }
	Vec2 GetDirection() { return m_direction; }

	void SetSpeed(float spd);
	void SetStartSpeed(float speed);
	void SetSpeedDecreaseRatio(float ratio) { m_speedDecreaseRatio = ratio; }
	void ReduceSpeed();
	
	void Explode() { m_isToExplode = true; }
	void Exploded() { m_isToExplode = false; }
	void StopAction() { m_isStopped = true; }
	void StopFlying() { m_isFlying = false; }
	void EraseMe() { m_toBeErased = true; }
	void Crashed() { m_lifeTime = BULLET_EXPLODE_TIME; }
	void Dead();

	bool IsToExplode() { return m_isToExplode; }
	bool IsActionStopped() { return m_isStopped; }
	bool IsBullet() { return true; }

	Sprite* GetSprite() { return m_spr; }

protected:
	void DecreaseLife();
	Sprite* MakeBody();
	Sprite* MakeDebris();
	void AddDebrisToParent();

	Sprite* m_body;
	Sprite* m_spr;
	Vec2 m_direction;

	float m_startSpeed;
	float m_speed;
	float m_speedSetRatio;
	float m_speedDecreaseRatio;

	float m_lifeTime;
	float m_startLife;
	float m_lifeDecrease;
	
	bool m_isToExplode;
	bool m_isStopped;
	
	Size m_screen;
	enum BULLET_CONFIG
	{
		BULLET_FRAMES = 5,
		BULLET_WIDTH = 10,
		BULLET_HEIGHT = 10,
		BULLET_RATIO = 2,

		BULLET_LIFETIME = 9,
		BULLET_LIFE_DECREASE_DELTA = 1,
		BULLET_EXPLODE_TIME = 0,
		BULLET_REDUCTION_SPEED_TIME = 3,
	};
};