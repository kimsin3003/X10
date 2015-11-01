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
	if (explosion == nullptr)
		return;

	float dmg = explosion->calcDmg(this->getPositionX(), this->getPositionY());
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