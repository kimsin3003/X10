#include "stdafx.h"
#pragma once;
#include "Mirror.h"
#include "Bullet.h"

bool Mirror::init()
{
	if (!Layer::init())
		return false;

	Size viewSize = Director::getInstance()->getVisibleSize();
	mySprite = Sprite::create("res/angel.png");
	mySprite->setAnchorPoint(Point(0.5, 0));
	mySprite->setPosition(Point(viewSize.width / 4, viewSize.height / 2));
	mySprite->setScaleX(0.4);
	mySprite->setScaleY(0.4);

	this->addChild(mySprite);

	return true;
}

void Mirror::SetEffect(Bullet& bullet)
{
	bullet.SetDirection(Vec2(-bullet.GetDirection().x, bullet.GetDirection().y));
}
