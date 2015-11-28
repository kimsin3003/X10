#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"

bool Enemy::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_spr = Sprite::create(FILE_ENEMY);
	addChild(m_spr);
	m_isEnemy = true;

	return true;
}

void Enemy::ToBullet(Bullet* bullet)
{
	bullet->Crashed(); 
}

void Enemy::ToSelf(const Bullet* bullet)
{
	m_spr->removeFromParent();
	m_spr = Sprite::create(FILE_ENEMY_DEAD);
	addChild(m_spr);
	m_spr->setScale(0.03f);
	this->removeFromParent();
	m_toBeErased = true;
}

void Enemy::ToSelf(const Explosion* explosion)
{
	ToSelf(static_cast<Bullet*>(NULL));
	m_toBeErased = true;
}
