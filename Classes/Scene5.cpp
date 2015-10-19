#include "Scene5.h"
#include "Scene6.h"

Scene* Scene5::createScene()
{
	auto scene = Scene::create();

	auto layer = Scene5::create();
	scene->addChild(layer);

	return scene;
}

bool Scene5::init()
{
	if (!Layer::init())
	{
		return false;
	}


	auto item = MenuItemFont::create("Goto Scene6",
		CC_CALLBACK_1(Scene5::ChangeScene, this));

	auto menu = Menu::create(item, NULL);
	menu->alignItemsHorizontally();
	this->addChild(menu);

	return true;
}


void Scene5::ChangeScene(Ref* sender)
{
	Director::getInstance()->replaceScene(Scene6::createScene());
}