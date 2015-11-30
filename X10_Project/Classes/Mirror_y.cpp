#include "stdafx.h"
#include "Mirror_y.h"
#include "Bullet.h"
#include "FileStuff.h"

namespace FileStuff
{
	const string MIRROR_Y = "res/target/flat_mirror.png";
}

bool Mirror_y::init()
{
	if (!Target::init())
	{
		return false;
	}

	m_isEnemy = false;
	m_spr = Sprite::create(FileStuff::MIRROR_Y);
	addChild(m_spr);

	return true;
}

void Mirror_y::ToBullet(Bullet* bullet)
{
	Vec2 curDir = bullet->GetDirection();
	Vec2 reflect = Vec2(curDir.x , curDir.y * -1);
	bullet->SetDirection(reflect); 
}

void Mirror_y::ToSelf(const Bullet* bullet)
{
	if (m_applyEffectToMe)
	{
		m_applyEffectToMe = false;
	}
}

void Mirror_y::ToSelf(const Explosion* explosion)
{

}
