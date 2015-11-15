#pragma once
#include "Target.h"

class Enemy : public Target
{
public:
	CREATE_FUNC(Enemy);
	virtual const Rect& GetBoundingArea() override;
	bool init() override;

protected:
	void ToBullet(Bullet* collider) override;
	void ToExplosion(Explosion* explosion) override;
	void ToSelf(const Bullet* bullet) override;
	void ToSelf(const Explosion* explosion) override;


	const string FILE_ENEMY = "res/enemy.png";
	const string FILE_ENEMY_DEAD = "res/enemy_dead.png";
};