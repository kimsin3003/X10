#include "stdafx.h"
#include "Target.h"
#include "Virtical_Mirror.h"
#include "FileStuff.h"
#include "Bullet.h"
#include <math.h>
#include <SimpleAudioEngine.h>

bool Virtical_Mirror::init()
{
	if (!Target::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FileStuff::SOUND_MIRROR);

	m_spr = Sprite::create(FileStuff::VIRTICAL_MIRROR);
	addChild(m_spr);

	return true;
}

void Virtical_Mirror::ToBullet(Bullet* bullet)
{
	float mirror_angle = (360 - this->getRotation()) * M_PI / 180;
	float d = (2 * M_PI + (-bullet->GetDirection()).getAngle());
	float inci_angle = (2 * M_PI + (-bullet->GetDirection()).getAngle()) - mirror_angle;

	if (inci_angle <= M_PI)
	{
		float ref_angle = (M_PI - inci_angle) + mirror_angle;
		bullet->SetDirection(bullet->GetDirection().length() * Vec2(cos(ref_angle), sin(ref_angle)));
	}
	else
	{
		float ref_angle = (3 * M_PI - inci_angle) + mirror_angle;
		bullet->SetDirection(bullet->GetDirection().length() * Vec2(cos(ref_angle), sin(ref_angle)));
	}
}

void Virtical_Mirror::ToSelf(const Bullet* bullet)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
		FileStuff::SOUND_MIRROR);
}

void Virtical_Mirror::ToSelf(const Explosion* explosion)
{

}