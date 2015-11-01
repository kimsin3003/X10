#include "stdafx.h"
#include "Enemy.h"

Sprite* Enemy::createEnemy()
{
	auto enemy = Sprite::create();
	auto bodySprite = Sprite::create("res/alien.png");
	enemy->addChild(bodySprite);

	return enemy;
}

bool Enemy::init()
{
	if (Sprite::init() == false)
		return false;

	return true;
}

int Enemy::getHp() const
{
	return hp;
}

void Enemy::hitByExplosion(Explosion* explosion)
{

}