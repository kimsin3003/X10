#include "stdafx.h"
#include "Enemy.h"
#include "Explosion.h"

Enemy* Enemy::createEnemy()
{
	auto enemy = Enemy::create();
	auto body = Sprite::create("res/alien.png");
	enemy->addChild(body);

	return enemy;
}

bool Enemy::init()
{
	if (Node::init() == false)
		return false;

	this->maxHp = ENEMY_CONST::DEFAULT_HP;
	this->hp = ENEMY_CONST::DEFAULT_HP;

	return true;
}

float Enemy::getHp() const
{
	return hp;
}

void Enemy::hitByExplosion(Explosion* explosion, float distance)
{
	if (explosion == nullptr)
		return;
	float dmg = explosion->calcDmg(this->getPositionX(), this->getPositionY(), distance);
	CCLOG("hp: %f, dmg = %f", hp, dmg); 

	if (dmg >= hp)
	{
		hp = 0;
		die();
	}
	else {
		hp -= dmg;
	}

}

void Enemy::die()
{
	this->removeFromParent();
}