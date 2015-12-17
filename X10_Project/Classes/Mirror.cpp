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

	return true;
}

void Mirror::ToBullet(Bullet* bullet)
{
	//미러 기준의 입사각.
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
