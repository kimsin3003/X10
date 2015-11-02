#pragma once
#include "cocos2d.h"
class Explosion;

class Enemy : public Node
{
private:
	Sprite* body;
	float	maxHp;
	float hp;
public:
	static Enemy* createEnemy();
	virtual bool init();
	float getHp() const;
	void hitByExplosion(Explosion* E, float distance);
	void die();

	CREATE_FUNC(Enemy);
};

