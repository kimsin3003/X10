#pragma once
#include "Target.h"

class Enemy : public Target
{
public:
	CREATE_FUNC(Enemy);
	bool init() override;

protected:
	void ToBullet(Bullet* bullet) override;
	void ToSelf(const Bullet* bullet) override;
	void ToSelf(const Explosion* explosion) override;

	const string FILE_ENEMY = "res/enemy.png";
	const string FILE_ENEMY_DEAD = "res/enemy_dead.png";
};