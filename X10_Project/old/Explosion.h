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
	void boomRepeat(const float time);
	float calcDmg(float enemyX, float enemeyY, const float distance);
	void makeBigger(Node* body);
	static void boom(Scene* scene, Point p);

	CREATE_FUNC(Explosion);
};