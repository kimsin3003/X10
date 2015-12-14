#include "stdafx.h"
#include "MainScene.h"
#include "JWScene.h"
#include "ConstVars.h"

Scene* JWScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = JWScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool JWScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,25)))
	{
		return false;
	}

	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 0);

	auto winSize = Director::getInstance()->getWinSize();

	auto GotoMainScene = MenuItemFont::create("Reset Complete", CC_CALLBACK_1(JWScene::ChangeToMainScene, this));
	auto GotoMainSceneMenu = Menu::create(GotoMainScene, NULL);
	GotoMainSceneMenu->setPosition(winSize.width/2, winSize.height/2);
	this->addChild(GotoMainSceneMenu);

	return true;
}

void JWScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}