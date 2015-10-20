#include "Scene2.h"
#include "Scene3.h"

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

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Scene2::nextSceneCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width/2 - closeItem->getContentSize().width / 2,
		origin.y + visibleSize.height/2 + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}


void Scene2::nextSceneCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(Scene3::createScene());

}
