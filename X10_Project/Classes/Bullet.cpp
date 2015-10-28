#include "stdafx.h"
#include "Bullet.h"

Scene* Bullet::createScene()
{
	Scene* scene = Scene::create();

	auto layer = Bullet::create();

	scene->addChild(layer);

	return scene;
}

bool Bullet::init()
{
	if (!Layer::init())
		return false;

	bullet = Sprite::create("res/bullet.png");
	bullet->setAnchorPoint(Point(0.5, 0));
	bullet->setScaleX(0.2);
	bullet->setScaleY(0.2);
	Size windowSize = Director::getInstance()->getVisibleSize();

	bullet->setPosition(Point(windowSize.width / 2, 10));
	this->addChild(bullet);

	return true;
}


void Bullet::Start()
{

}
