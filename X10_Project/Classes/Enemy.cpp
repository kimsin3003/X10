#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"
#include "FileStuff.h"

bool Enemy::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_isEnemy = true;
	m_spr = Sprite::create(FileStuff::ENEMY);
	addChild(m_spr);

	return true;
}

void Enemy::ToBullet(Bullet* bullet)
{
	//bullet->Crashed(); 
}

void Enemy::ToSelf(const Bullet* bullet)
{
	m_spr->removeFromParent();
	m_spr = Sprite::create(FileStuff::ENEMY_DEAD);
	addChild(m_spr);
	//m_spr->setScale(1.0f);
	this->removeFromParent();
	m_toBeErased = true;
}

void Enemy::ToSelf(const Explosion* explosion)
{
	ToSelf(static_cast<Bullet*>(NULL));
	m_toBeErased = true;
}
