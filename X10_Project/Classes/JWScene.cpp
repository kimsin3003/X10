#include "stdafx.h"
#include "MainScene.h"
#include "JWScene.h"
#include "Sling.h"

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
	if (!Layer::init())
	{
		return false;
	}

	Sling sling; 
	
	auto GotoMainScene = MenuItemFont::create("Go to MainScene", CC_CALLBACK_1(JWScene::ChangeToMainScene, this));
	auto GotoMainSceneMenu = Menu::create(GotoMainScene, NULL);
	GotoMainSceneMenu->setPosition(200, 200);
	this->addChild(GotoMainSceneMenu);
	this->addChild(sling.Stick);
	this->addChild(sling.Shooter);

	return true;
}

void JWScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}