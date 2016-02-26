#include "stdafx.h"
#include "Target.h"
#include "Mirror.h"
#include "FileStuff.h"
#include "Bullet.h"
#include <SimpleAudioEngine.h>

bool Mirror::init()
{
	if (!Target::init())
	{
		return false;
	}
	
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FileStuff::SOUND_MIRROR);

	m_spr = Sprite::create(FileStuff::MIRROR);
	addChild(m_spr);

	return true;
}

void Mirror::ToBullet(Bullet* bullet)
{
	float mirrorAngle = getRotation(); //�ſ��� ���򼱿��� ������ ���� (�ð����)
	Vec2 bulletDir = bullet->GetDirection();// �ҷ��� ���� ����
	
	float mirrorRadian = CC_DEGREES_TO_RADIANS(mirrorAngle);
	bulletDir.rotate(Vec2::ZERO, mirrorRadian); // ���͸� ���� ��ǥ��� ȸ�� (�ſ��� ������ ���� ����ϱ� ����...)
	
	bulletDir.x = -bulletDir.x; //������ ���� �ſ￡ �ݻ�
	bulletDir.rotate(Vec2::ZERO, -mirrorRadian); // ���� ��ǥ��� �ٽ� ȸ��

	Vec2 afterVec = bulletDir; // �ݻ��� ����
	bullet->SetDirection(bulletDir);

	float mirrorWidth = m_spr->getContentSize().width * getScale(); // �ſ��� �β�
}

void Mirror::ToSelf(const Bullet* bullet)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
		FileStuff::SOUND_MIRROR);
}

void Mirror::ToSelf(const Explosion* explosion)
{

}
