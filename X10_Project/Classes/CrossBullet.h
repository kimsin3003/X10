#pragma once

#include "Bullet.h"

class CrossBullet : public Bullet
{
public:
	CREATE_FUNC(CrossBullet);
	bool init();
	void Act();
	Explosion* GetExplosion();

private:
	CrossBullet();
	int m_pattern;

	enum PATTERN
	{
		MOVE,
		CENTER, 
		CROSS_LEFT,
		CROSS_RIGHT,
		CROSS_UP,
		CROSS_DOWN,
		DIE,
	};
	
	
	float tmp_BULLET_REDUCTIONSPEEDTIME; //임시로 
	const float DELTA_POS; //constructor 에서 초기화
	const float DELTA_TIME = 0.5f;
};