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
	void SetSpeed(float spd);
	void SetStartSpeed(float speed);
	void SetSpeedDecreaseRatio(float ratio) { m_speedDecreaseRatio = ratio; }
	const Rect& GetBoundingArea();
	
	bool IsBullet() { return true; }
	bool ShouldExplode() { return m_shouldExplode; }

	void Crashed();
	void Explode() { m_shouldExplode = true; }
	void Exploded() { m_shouldExplode = false; }
	void TimeUp();
	void ReduceSpeed();
	void StopAction() { m_stopAction = true; }
	bool IsActing() { return m_stopAction; }
	void StopFlying() { m_isFlying = false; }
	void EraseOn() { m_toBeErased = true; }
protected:
	void DecreaseLife();
	void AddDebrisToParent();
	Sprite* MakeDebris();
	Sprite* MakeBody();
	Sprite* m_body;

	Vec2 m_direction;
	float m_startLife;
	float m_startSpeed;
	float m_speed;
	float m_lifeTime;
	float m_lifeDecrease;
	float m_speedSetRatio;
	float m_speedDecreaseRatio;

	bool m_shouldExplode;
	bool m_stopAction;
	const char* FILE_NAME= "res/firework.png";

	Size m_screen;

	enum BULLET_CONFIG
	{
		BULLET_FRAMES = 5,
		BULLET_WIDTH = 10,
		BULLET_HEIGHT = 10,
		BULLET_RATIO = 2,

		BULLET_LIFETIME = 30,
		BULLET_EXPLODETIME = 0,
		BULLET_REDUCTIONSPEEDTIME = 3,
	};
};