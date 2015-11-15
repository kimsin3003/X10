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
	return true;
}

//효과가 한번만 적용되는게 아니라 계속 적용됨 
//한번만 방향을 바꿔주는게 아니라 계에속 방향을 바꿔주게됨
//그래서 진동하는 총알의 모습이...
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
	//효과가 한번만 적용되는게 아니라 계에에속 적용됨 
	//-> 문제해결 필요 (버블과 클라우드에서는 해결, 한번 충돌했을 때 터트리면 되니까)

	spr->removeFromParent();
	spr = Sprite::create(FILE_MIRROR_ANGRY);
	addChild(spr);
	sprScaleRatio *= 1.01f; //1.01배가 충돌해 있는 동안 계에에에에속 적용됨
	spr->setScale(sprScaleRatio);
}

void Mirror::ToSelf(const Explosion* explosion)
{

}
