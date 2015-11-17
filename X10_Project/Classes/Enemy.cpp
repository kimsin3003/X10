#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"

bool Enemy::init()
{
	m_spr = Sprite::create(FILE_ENEMY);
	addChild(m_spr);

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

///# 아래 두 ToSelf는 사실상 같은거 아닌가? Bullet과 Explosion모두 Collider의 자식이면 ToSelf(const Collider* bullet) 하나만 있어도 되지?
void Enemy::ToSelf(const Bullet* bullet)
{
	m_spr->removeFromParent();
	m_spr = Sprite::create(FILE_ENEMY_DEAD);
	addChild(m_spr);
	m_spr->setScale(0.03f);
	this->removeFromParent();
}

void Enemy::ToSelf(const Explosion* explosion)
{
	m_spr->removeFromParent();
	m_spr = Sprite::create(FILE_ENEMY_DEAD);
	addChild(m_spr);
	m_spr->setScale(0.03f);
	this->removeFromParent();
}
