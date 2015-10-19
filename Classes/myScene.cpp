#include "myScene.h"

USING_NS_CC;

Scene* myScene::scene()
{
	Scene* myscene = Scene::create();
	myScene* layer = myScene::create();
	myscene->addChild(layer);

	auto scene = TransitionCrossFade::create(1.0, myscene);

	return scene;
}

bool myScene::init()
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