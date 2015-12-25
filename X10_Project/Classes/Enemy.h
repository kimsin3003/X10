#pragma once

#include "Target.h"

class Enemy : public Target
{
public:
	CREATE_FUNC(Enemy);
	bool init();
	bool IsEnemy() { return true; }

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

	enum
	{
		DESTRUCT_FRAMES = 23
	};
};