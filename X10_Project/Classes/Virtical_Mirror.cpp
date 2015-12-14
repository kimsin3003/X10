#include "stdafx.h"
#include "Target.h"
#include "Virtical_Mirror.h"
#include "FileStuff.h"
#include "Bullet.h"

bool Virtical_Mirror::init()
{
	if (!Target::init())
	{
		return false;
	}
	m_spr = Sprite::create(FileStuff::VIRTICAL_MIRROR);
	addChild(m_spr);

	return true;
}

void Virtical_Mirror::ToBullet(Bullet* bullet)
{
	Vec2 curDir = bullet->GetDirection();
	Vec2 reflect = Vec2(curDir.x , curDir.y * -1);
	bullet->SetDirection(reflect); 
}

void Virtical_Mirror::ToSelf(const Bullet* bullet)
{

}

void Virtical_Mirror::ToSelf(const Explosion* explosion)
{

}
