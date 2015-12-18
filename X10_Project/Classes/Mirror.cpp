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
	float mirrorAngle = getRotation(); //거울이 수평선에서 기울어진 정도 (시계방향)
	Vec2 bulletDir = bullet->GetDirection(); // 불렛의 속도벡터
	
	float mirrorRadian = CC_DEGREES_TO_RADIANS(mirrorAngle);
	bulletDir.rotate(Vec2::ZERO, mirrorRadian); // 벡터를 수평 죄표계로 회전 (거울이 수직일 경우로 계산하기 위해...)
	
	bulletDir.x = -bulletDir.x; //가상의 수직 거울에 반사
	bulletDir.rotate(Vec2::ZERO, -mirrorRadian); // 원래 좌표계뢰 다시 회전
	
	bullet->SetDirection(bulletDir);
	getBoundingBox();

	//미러 기준의 입사각.
	/*float m = this->getRotation();
	float inci_angle = (-bullet->GetDirection()).getAngle() - this->getRotation();
	if (inci_angle <= 180){
		float ref_angle = (180 - inci_angle) + this->getRotation();
		bullet->SetDirection(Vec2(cos(ref_angle), sin(ref_angle)));
	}

	else{
		float ref_angle = (540 - inci_angle) + this->getRotation();
		bullet->SetDirection(Vec2(cos(ref_angle), sin(ref_angle)));
	}*/
}

void Mirror::ToSelf(const Bullet* bullet)
{
	
}

void Mirror::ToSelf(const Explosion* explosion)
{

}
