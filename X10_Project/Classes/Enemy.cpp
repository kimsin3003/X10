#include "stdafx.h"
#include "Enemy.h"
#include "FileStuff.h"
#include "Bullet.h"

bool Enemy::init()
{
	if (!Target::init())
	{
		return false;
	}
	m_spr = Sprite::create(FileStuff::ENEMY);
	addChild(m_spr);

	return true;
}

void Enemy::ToBullet(Bullet* bullet)
{

}

void Enemy::ToSelf(const Bullet* bullet)
{
	m_toBeErased = true;
}

void Enemy::ToSelf(const Explosion* explosion)
{
	ToSelf(static_cast<Bullet*>(NULL));
}
