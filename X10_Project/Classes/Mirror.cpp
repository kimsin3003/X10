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
	spr->setScale(3.0f);
	return true;
}
// 
// void Mirror::ApplyCollisionEffect(Collider* collider)
// {
// 	if (collider->IsBullet())
// 	{
// 		ToBullet(static_cast<Bullet*>(collider));
// 		ToSelf(static_cast<Bullet*>(collider));
// 	}
// 	else
// 	{
// 		ToExplosion(static_cast<Explosion*>(collider));
// 		ToSelf(static_cast<Explosion*>(collider));
// 	}
// }

void Mirror::ToBullet(Bullet* bullet)
{
	Vec2 curDir = bullet->GetDirection();
	Vec2 reflect = Vec2(curDir.x * -1, curDir.y);
	bullet->SetDirection(reflect);
}

void Mirror::ToExplosion(Explosion* explosion)
{

}

void Mirror::ToSelf(const Bullet* bullet)
{
	spr->removeFromParent();
	spr = Sprite::create(FILE_MIRROR_ANGRY);
	addChild(spr);
	spr->setScale(spr->getScale()+0.5);
}

void Mirror::ToSelf(const Explosion* explosion)
{

}

const Rect& Mirror::GetBoundingArea()
{
	return Rect(getPosition(), spr->getContentSize());
}
