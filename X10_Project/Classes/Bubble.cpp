#include "stdafx.h"
#include "Target.h"
#include "Bubble.h"

//방울 컨셉: 물방울에 갇힌 요정 
//구해주려고 터트렸더니...... 펑
bool Bubble::init()
{
	spr = Sprite::create(FILE_BUBBLE);
	addChild(spr);
	applyEffectToMe = true;

	return true;
}

void Bubble::ToBullet(Bullet* collider)
{

}

void Bubble::ToExplosion(Explosion* explosion)
{

}

//ToSelf가 굳이 구별되어야 하는지에 대해 의문
//총알에 맞든지, 폭발물에 맞든지 자기한테 적용되는 효과는 같음
//나중에 컨셉에 따라 구별될지 모르니까 일단 내비둠
void Bubble::ToSelf(const Bullet* bullet)
{
	if (applyEffectToMe)
	{
		applyEffectToMe = false;

		spr->setVisible(false); //임시 코드, 
								//타깃 매니저가 들고 있는 targets에서 제거해주는 게 맞는데
								//그렇게 하려면 타깃 매니저를 매개변수로 전달해야함

		Sprite* spr_00 = Sprite::create(FILE_BUBBLE_POP);
		spr_00->setScale(sprScaleRatio);
		addChild(spr_00);
		Sequence* action = Sequence::create(
			DelayTime::create(0.5f),
			RemoveSelf::create(),
			NULL);
		spr_00->runAction(action);
	}
}

void Bubble::ToSelf(const Explosion* explosion)
{
	if (applyEffectToMe)
	{
		applyEffectToMe = false;

		spr->setVisible(false); //임시 코드, 
								//타깃 매니저가 들고 있는 targets에서 제거해주는 게 맞는데
								//그렇게 하려면 타깃 매니저를 매개변수로 전달해야함

		Sprite* spr_00 = Sprite::create(FILE_BUBBLE_POP);
		spr_00->setScale(sprScaleRatio);
		addChild(spr_00);
		Sequence* action = Sequence::create(
			DelayTime::create(0.5f),
			RemoveSelf::create(),
			NULL);
		spr_00->runAction(action);
	}
}

