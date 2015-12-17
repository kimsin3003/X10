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
	//�̷� ������ �Ի簢.
	float m = this->getRotation();
	float inci_angle = (-bullet->GetDirection()).getAngle() - this->getRotation();
	if (inci_angle <= 180){
		float ref_angle = (180 - inci_angle) + this->getRotation();
		bullet->SetDirection(Vec2(cos(ref_angle), sin(ref_angle)));
	}

	else{
		float ref_angle = (540 - inci_angle) + this->getRotation();
		bullet->SetDirection(Vec2(cos(ref_angle), sin(ref_angle)));
	}
}

void Mirror::ToSelf(const Bullet* bullet)
{
	
}

void Mirror::ToSelf(const Explosion* explosion)
{

}
