#include "stdafx.h"
#include "Enemy.h"

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

	this->maxHp = 1000;
	this->hp = 1000;

	return true;
}

int Enemy::getHp() const
{
	return hp;
}

void Enemy::hitByExplosion(Explosion* explosion)
{

}