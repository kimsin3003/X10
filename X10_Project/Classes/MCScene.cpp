#include "stdafx.h"
#include "MainScene.h"
#include "MCScene.h"

Scene* MCScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MCScene::create();

	scene->addChild(layer);

	return scene;
}

bool MCScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto GotoMainScene = MenuItemFont::create("Go to MainScene", CC_CALLBACK_1(MCScene::ChangeToMainScene, this));
	auto GotoMainSceneMenu = Menu::create(GotoMainScene, NULL);
	GotoMainSceneMenu->setPosition(200, 200);
	this->addChild(GotoMainSceneMenu);

	return true;
}

void MCScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}