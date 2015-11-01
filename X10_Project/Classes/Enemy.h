#pragma once
#include "cocos2d.h"
class Explosion;

class Enemy : public Sprite
{
private:
	int	maxHp;
	int hp;
public:
	static cocos2d::Sprite* createEnemy();
	virtual bool init();
	int getHp() const;
	void hitByExplosion(Explosion* E);
};

