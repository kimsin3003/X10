#pragma once
#include "cocos2d.h"
class Explosion;

namespace ENEMY_CONST ///# 상수 하나를 위해 네임스페이스를?? 그냥 상수 모음은 config.h같은데로 빼서 한꺼번에 관리하면 편하다.
{
	const float DEFAULT_HP = 1000;
}

class Enemy : public Node
{
private: ///# 코딩 컨벤션: 클래스마다 private를 먼저 놓을지 public을 먼저 놓을지 정하고 통일되게..
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

