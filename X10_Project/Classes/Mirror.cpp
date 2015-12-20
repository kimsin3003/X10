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
	float mirrorAngle = getRotation(); //�ſ��� ���򼱿��� ������ ���� (�ð����)
	Vec2 bulletDir = bullet->GetDirection(); // �ҷ��� �ӵ�����
	
	float mirrorRadian = CC_DEGREES_TO_RADIANS(mirrorAngle);
	bulletDir.rotate(Vec2::ZERO, mirrorRadian); // ���͸� ���� ��ǥ��� ȸ�� (�ſ��� ������ ���� ����ϱ� ����...)
	
	bulletDir.x = -bulletDir.x; //������ ���� �ſ￡ �ݻ�
	bulletDir.rotate(Vec2::ZERO, -mirrorRadian); // ���� ��ǥ��� �ٽ� ȸ��
	
	bullet->SetDirection(bulletDir);
	getBoundingBox();

	//�̷� ������ �Ի簢.
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
