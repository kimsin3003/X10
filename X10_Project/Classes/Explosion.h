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
	static Explosion* createExplosion();
	
	virtual bool init();
	void boom(const float time);
	float calcDmg(float enemyX, float enemeyY, const float distance);
	void makeBigger(Node* body);

	CREATE_FUNC(Explosion);
};