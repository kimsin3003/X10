#pragma once
#include "cocos2d.h"
class Explosion;

class Enemy : public Node
{
private:
	Sprite* body;
	int	maxHp;
	int hp;
public:
	static Enemy* createEnemy();
	virtual bool init();
	int getHp() const;
	void hitByExplosion(Explosion* E);
	void die();

	CREATE_FUNC(Enemy);
};

