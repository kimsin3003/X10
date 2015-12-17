#include "stdafx.h"
#include "Target.h"
#include "Mirror.h"
#include "FileStuff.h"
#include "Bullet.h"

bool Mirror::init()
{
	if (!Target::init())
	{
		return false;
	}
	m_spr = Sprite::create(FileStuff::MIRROR);
	addChild(m_spr);
	Size sizeSpr = m_spr->getContentSize();
	Size sizeMain = this->getContentSize();
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
	
}

void Mirror::ToSelf(const Explosion* explosion)
{

}
