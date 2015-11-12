#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"

#include "Mirror.h"

bool Mirror::init()
{
	spr = Sprite::create(FILE_MIRROR);
	addChild(spr);

	//테스트용 코드
	setScale(3.0f);
	setPosition(30, 200);
	return true;
}

void Mirror::ApplyCollisionEffect(Collider* collider)
{
	if (collider->IsBullet())
	{
		ToBullet((Bullet*)collider);
		ToSelf((Bullet*)collider);
	}
	else
	{
		ToExplosion((Explosion*)collider);
		ToSelf((Explosion*)collider);
	}
}

void Mirror::ToBullet(Bullet* bullet)
{
	Vec2 curDir = bullet->GetDirection();
	Vec2 reflect = Vec2(curDir.x * -1, curDir.y);
	bullet->SetDirection(reflect);
}

void Mirror::ToExplosion(Explosion* explosion)
{

}

void Mirror::ToSelf(Bullet* bullet)
{
	spr = Sprite::create(FILE_MIRROR_ANGRY);
	setScale(1.5);
}

void Mirror::ToSelf(Explosion* explosion)
{

}