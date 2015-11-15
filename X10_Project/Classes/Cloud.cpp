#include "stdafx.h"
#include "Target.h"
#include "Collider.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Cloud.h"

bool Cloud::init()
{
	spr = Sprite::create(FILE_CLOUD);
	addChild(spr);
	applyEffectToMe = true;

	return true;
}

void Cloud::ToBullet(Bullet* collider)
{

}

void Cloud::ToExplosion(Explosion* explosion)
{

}

//ToSelf가 굳이 구별되어야 하는지에 대해 의문
//총알에 맞든지, 폭발물에 맞든지 자기한테 적용되는 효과는 같음
//나중에 컨셉에 따라 구별될지 모르니까 일단 내비둠
void Cloud::ToSelf(const Bullet* bullet)
{
	if (applyEffectToMe)
	{
		applyEffectToMe = false;

		spr->setVisible(false); //임시 코드, 
								//타깃 매니저가 들고 있는 targets에서 제거해주는 게 맞는데
								//그렇게 하려면 타깃 매니저를 매개변수로 전달해야함

		Sprite* spr_00 = Sprite::create(FILE_CLOUD_LEFT);
		Sprite* spr_01 = Sprite::create(FILE_CLOUD_RIGHT);
		addChild(spr_00);
		addChild(spr_01);

		spr_00->setPosition(Vec2(-20, 0));
		spr_01->setPosition(Vec2(20, 0));

		Sequence* action_00 = Sequence::create(
			MoveBy::create(1.0f, Vec2(-30, 0)),
			RemoveSelf::create(),
			NULL);
		Sequence* action_01 = Sequence::create(
			MoveBy::create(1.0f, Vec2(30, 0)),
			RemoveSelf::create(),
			NULL);

		spr_00->runAction(action_00);
		spr_01->runAction(action_01);

		spr_00->setScale(sprScaleRatio);
		spr_01->setScale(sprScaleRatio);
	}
}

void Cloud::ToSelf(const Explosion* explosion)
{
	if (applyEffectToMe)
	{
		applyEffectToMe = false;

		spr->setVisible(false); //임시 코드, 
								//타깃 매니저가 들고 있는 targets에서 제거해주는 게 맞는데
								//그렇게 하려면 타깃 매니저를 매개변수로 전달해야함

		Sprite* spr_00 = Sprite::create(FILE_CLOUD_LEFT);
		Sprite* spr_01 = Sprite::create(FILE_CLOUD_RIGHT);
		addChild(spr_00);
		addChild(spr_01);

		spr_00->setPosition(Vec2(-20, 0));
		spr_01->setPosition(Vec2(20, 0));

		Sequence* action_00 = Sequence::create(
			MoveBy::create(1.0f, Vec2(-30, 0)),
			RemoveSelf::create(),
			NULL);
		Sequence* action_01 = Sequence::create(
			MoveBy::create(1.0f, Vec2(30, 0)),
			RemoveSelf::create(),
			NULL);

		spr_00->runAction(action_00);
		spr_01->runAction(action_01);

		spr_00->setScale(sprScaleRatio);
		spr_01->setScale(sprScaleRatio);
	}
}

