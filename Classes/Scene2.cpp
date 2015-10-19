#include "Scene2.h"

USING_NS_CC;

Scene* Scene2::scene()
{
	auto scene = Scene::create();
	auto layer = Scene2::create();
	scene->addChild(layer);

	return scene;
}

bool Scene2::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("NiceMan.jpg");
	sprite->setScale(0.5);
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	return true;
}