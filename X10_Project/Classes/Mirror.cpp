#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Mirror.h"

bool Mirror::init()
{
	m_spr = Sprite::create(FILE_MIRROR);
	addChild(m_spr);
	return true;
}

void Mirror::ToBullet(Bullet* bullet)
{
	Vec2 curDir = bullet->GetDirection();
	Vec2 reflect = Vec2(curDir.x * -1, curDir.y);
	bullet->SetDirection(reflect);
}

void Mirror::ToExplosion(Explosion* explosion)
{

}

void Mirror::ToSelf(const Bullet* bullet)
{
	m_spr->removeFromParent();
	m_spr = Sprite::create(FILE_MIRROR_ANGRY);
	addChild(m_spr);
	m_sprScaleRatio *= 1.05f;
	m_spr->setScale(m_sprScaleRatio);
}

void Mirror::ToSelf(const Explosion* explosion)
{

}
