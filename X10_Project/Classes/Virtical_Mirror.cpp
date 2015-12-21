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
	m_spr = Sprite::create(FileStuff::VIRTICAL_MIRROR);
	addChild(m_spr);

	return true;
}

void Virtical_Mirror::ToBullet(Bullet* bullet)
{
	//미러 기준의 입사각 in radian.
	float mirror_angle = (360 - this->getRotation()) * M_PI / 180;
	float d = (2 * M_PI + (-bullet->GetDirection()).getAngle());
	float inci_angle = (2 * M_PI + (-bullet->GetDirection()).getAngle()) - mirror_angle;

	if (inci_angle <= M_PI){
		float ref_angle = (M_PI - inci_angle) + mirror_angle;
		bullet->SetDirection(bullet->GetDirection().length() * Vec2(cos(ref_angle), sin(ref_angle)));
	}

	else{
		float ref_angle = (3 * M_PI - inci_angle) + mirror_angle;
		bullet->SetDirection(bullet->GetDirection().length() * Vec2(cos(ref_angle), sin(ref_angle)));
	}
}

void Virtical_Mirror::ToSelf(const Bullet* bullet)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/sound_effects/metal_ting.mp3", false, 1.0f, 0, 0);
}

void Virtical_Mirror::ToSelf(const Explosion* explosion)
{

}

// const Rect Virtical_Mirror::GetBoundingArea()
// {
// 	Vector<Rect> areas;
// 	for (int i = 0; i < this->getScaleY() * m_spr->getContentSize().width; i++){
// 		this->getRotation();
// 		areas.pushBack(Rect(this->getPosition().x));
// 	}
// 	return 
// }
