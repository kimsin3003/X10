#include "stdafx.h"
#include "MainScene.h"
#include "MCScene.h"

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	/*Secret Paul's Test Page*/
	auto PaulItem = MenuItemFont::create("p", CC_CALLBACK_1(MainScene::ChangeToMCScene,this));
	PaulItem->setScale(0.2);
	PaulItem->setPosition(Vec2(origin.x + visibleSize.width - PaulItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height + PaulItem->getContentSize().height/2));
	
	auto menu = Menu::create(closeItem, PaulItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void MainScene::ChangeToMCScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MCScene::createScene());
	return;
}

void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
