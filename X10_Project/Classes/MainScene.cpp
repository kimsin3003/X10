#include "stdafx.h"
#include "MainScene.h"
#include "JWScene.h"
#include "TWScene.h"
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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	//Paul's test Page
	auto labelMC = MenuItemFont::create("Paul's Test page", CC_CALLBACK_1(MainScene::ChangeSceneToMC, this));

	auto menuMC = Menu::create(labelMC, NULL);
	menuMC->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - labelMC->getContentSize().height));

	auto textHeight = labelMC->getContentSize().height;

	this->addChild(menuMC);


	//Taewoo's test Page
	auto labelTW = MenuItemFont::create("Kimsin's Test page", CC_CALLBACK_1(MainScene::ChangeSceneToTW, this));

	auto menuTW = Menu::create(labelTW, NULL);
	menuTW->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - textHeight * 3));

	this->addChild(menuTW);

	//Jinwuk's test Page
	auto labelJW = MenuItemFont::create("FeaterHub's Test page", CC_CALLBACK_1(MainScene::ChangeSceneToJW, this));

	auto menuJW = Menu::create(labelJW, NULL);
	menuJW->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - textHeight * 5));

	this->addChild(menuJW);


    
    return true;
}

void MainScene::ChangeSceneToMC(Ref* pSender)
{
	Director::getInstance()->replaceScene(MCScene::createScene());
}

void MainScene::ChangeSceneToTW(Ref* pSender)
{
	Director::getInstance()->replaceScene(TWScene::createScene());
}

void MainScene::ChangeSceneToJW(Ref* pSender)
{
	Director::getInstance()->replaceScene(JWScene::createScene());
}

void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
