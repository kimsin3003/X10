#include "Scene6.h"
#include "Scene1.h"

Scene* Scene6::createScene()
{
	auto scene = Scene::create();

	auto layer = Scene6::create();
	scene->addChild(layer);

	return scene;
}

bool Scene6::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto item = MenuItemFont::create("Goto Scene1", 
		CC_CALLBACK_1(Scene6::ChangeScene, this));

	auto menu = Menu::create(item, NULL);
	menu->alignItemsHorizontally();
	this->addChild(menu);

	return true;
}

void Scene6::ChangeScene(Ref* sender)
{
	Director::getInstance()->replaceScene(Scene1::createScene());
}