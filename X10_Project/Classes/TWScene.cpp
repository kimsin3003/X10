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

	auto mainTitle = Label::createWithTTF("Main Title\n fuck!!!!", "fonts/NanumGothic.ttf", 34);
	mainTitle->setPosition(Point(160, 240));
	this->addChild(mainTitle);
	return true;
}

void TWScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}