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

	//direction
	void SetDirection(Vec2 dir) { m_direction = dir; }
	Vec2 GetDirection() { return m_direction; }

	//speed
	void SetSpeed(float spd);
	void SetStartSpeed(float speed);
	void SetSpeedDecreaseRatio(float ratio) { m_speedDecreaseRatio = ratio; }
	void ReduceSpeed();
	
	const Rect& GetBoundingArea();
	
	//status
	void Explode() { m_isToExplode = true; }
	void Exploded() { m_isToExplode = false; }
	bool IsToExplode() { return m_isToExplode; }
	bool IsActionStopped() { return m_isStopped; }
	void StopAction() { m_isStopped = true; }
	void StopFlying() { m_isFlying = false; }
	void EraseMe() { m_toBeErased = true; }
	bool IsBullet() { return true; }
	void Crashed();
	void TimeUp();

protected:
	void DecreaseLife();
	Sprite* MakeDebris();
	void AddDebrisToParent();
	Sprite* MakeBody();

	Sprite* m_body;
	Vec2 m_direction;

	//speed
	float m_startSpeed;
	float m_speed;
	float m_speedSetRatio;
	float m_speedDecreaseRatio;

	//life
	float m_lifeTime;
	float m_startLife;
	float m_lifeDecrease;
	
	//status
	bool m_isToExplode;
	bool m_isStopped;
	
	//setting
	Size m_screen;
	enum BULLET_CONFIG
	{
		BULLET_FRAMES = 5,
		BULLET_WIDTH = 10,
		BULLET_HEIGHT = 10,
		BULLET_RATIO = 2,

		BULLET_LIFETIME = 3,
		BULLET_LIFE_DECREASE_DELTA = 1,
		BULLET_EXPLODE_TIME = 0,
		BULLET_REDUCTION_SPEED_TIME = 3,
	};
};