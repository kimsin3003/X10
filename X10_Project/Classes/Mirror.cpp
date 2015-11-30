#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Mirror.h"
#include "FileStuff.h"

namespace FileStuff
{
	const string MIRROR = "res/target/Mirror.png";
	const string MIRROR_ANGRY = "res/target/MirrorAngry.png";
}

bool Mirror::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_isEnemy = false;
	m_spr = Sprite::create(FileStuff::MIRROR);
	addChild(m_spr);

	return true;
}

void Mirror::ToBullet(Bullet* bullet)
{
	Vec2 curDir = bullet->GetDirection();
	Vec2 reflect = Vec2(curDir.x * -1, curDir.y);
	bullet->SetDirection(reflect);
}

void Mirror::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;

		m_spr->removeFromParent();
		m_spr = Sprite::create(FileStuff::MIRROR_ANGRY);
		addChild(m_spr);
		m_sprScaleRatio *= 1.1f;
		m_spr->setScale(m_sprScaleRatio);
	}
}

void Mirror::ToSelf(const Explosion* explosion)
{

}
