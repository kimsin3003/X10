#include "stdafx.h"
#include "MainScene.h"
#include "TWScene.h"

Scene* TWScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TWScene::create();

	scene->addChild(layer);

	return scene;
}

bool TWScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto GotoMainScene = MenuItemFont::create("Go to MainScene", CC_CALLBACK_1(TWScene::ChangeToMainScene, this));
	auto GotoMainSceneMenu = Menu::create(GotoMainScene, NULL);
	GotoMainSceneMenu->setPosition(200, 200);
	this->addChild(GotoMainSceneMenu);

	return true;
}

void TWScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}