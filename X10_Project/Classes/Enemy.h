#pragma once
#include "Target.h"

class Enemy : public Target
{
public:
	CREATE_FUNC(Enemy);
	bool init() override;
	//Item GetItem(){ return m_item; } 곧 필요해질듯

protected:
	void ToBullet(Bullet* bullet) override;
	void ToSelf(const Bullet* bullet) override;
	void ToSelf(const Explosion* explosion) override;

	const string FILE_ENEMY = "res/enemy.png";
	const string FILE_ENEMY_DEAD = "res/enemy_dead.png";
};