#include "MainScene.h"
#include "GameScene.h"

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

	auto item = MenuItemFont::create("Start Game", 
		CC_CALLBACK_1(MainScene::ChangeScene, this));

	auto menu = Menu::create(item, NULL);
	menu->alignItemsHorizontally();
	this->addChild(menu);

	return true;
}

void MainScene::ChangeScene(Ref* sender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}