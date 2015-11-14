#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"

bool Enemy::init()
{
	spr = Sprite::create(FILE_ENEMY);
	addChild(spr);
	//테스트용.
	spr->setScale(0.03f);
	setPosition(200, 400);
	return true;
}


void Enemy::ToBullet(Bullet* bullet)
{
	bullet->Crashed(); 
	bullet->removeFromParent();
}

void Enemy::ToExplosion(Explosion* explosion)
{

}

void Enemy::ToSelf(Bullet* bullet)
{
	spr->removeFromParent();
	spr = Sprite::create(FILE_ENEMY_DEAD);
	addChild(spr);
	spr->setScale(0.03f);
	this->removeFromParent();
}

void Enemy::ToSelf(Explosion* explosion)
{
	spr->removeFromParent();
	spr = Sprite::create(FILE_ENEMY_DEAD);
	addChild(spr);
	spr->setScale(0.03f);
	this->removeFromParent();
}

const Rect& Enemy::GetBoundingArea()
{
	return Rect(getPosition(), spr->getContentSize());
}

