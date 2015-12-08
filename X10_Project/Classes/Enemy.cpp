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
	///{@ 여기부터

	m_spr->removeFromParent();
	m_spr = Sprite::create(FileStuff::ENEMY_DEAD);
	addChild(m_spr);
	//m_spr->setScale(1.0f);
	this->removeFromParent();
	m_toBeErased = true;

	///@} 여기까지.... 사실은 BULLET과 상관 없이 내부 멤버 함수로 두고 아래의 ToSelf(const Explosion* explosion)에서 써먹어도 될 것 같은데..
}

void Enemy::ToSelf(const Explosion* explosion) ///# 이 ToSelf 함수 시그니쳐, 더 좋은 방법이 없는지 고민해볼 것.
{
	ToSelf(static_cast<Bullet*>(NULL)); ///# 같은 Collider부모 밑의 형제 타입(Bullet <-> Explosion)을 받는 함수를 강제 호출하는 것은 이상한데??
	m_toBeErased = true;
}
