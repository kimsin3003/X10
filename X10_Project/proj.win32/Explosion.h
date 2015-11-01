#pragma once
#include "cocos2d.h"
namespace EXPLOSION_CONST
{
	const int DEFAULT_DAMAGE = 500;
}

class Explosion : public Node
{
private:
	float mainDamage;
public:
	static cocos2d::Sprite* createExplosion(int dmg = EXPLOSION_CONST::DEFAULT_DAMAGE);
	
	virtual bool init();
	void boom();
};