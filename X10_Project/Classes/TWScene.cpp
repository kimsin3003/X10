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
	mainTitle->setName("MainTitle");

	Size winSize = Director::getInstance()->getVisibleSize();
	float labelWidth = mainTitle->getContentSize().width;
	float labelHeight = mainTitle->getContentSize().height;
	auto action1 = MoveTo::create(10.0 / labelHeight, Point(labelWidth / 2, winSize.height - labelHeight / 2));
	auto action2 = MoveTo::create(10.0 / labelWidth, Point(winSize.width - labelWidth / 2, winSize.height - labelHeight / 2));
	auto action3 = MoveTo::create(10.0 / labelHeight, Point(winSize.width - labelWidth / 2, labelHeight / 2));
	auto action4 = MoveTo::create(10.0 / labelWidth, Point(labelWidth / 2, labelHeight / 2));
	auto sequence_action = Sequence::create(action1, action2, action3, action4, NULL);
	auto forever_repeat_action = RepeatForever::create(sequence_action);

	mainTitle->runAction(forever_repeat_action);
	mainTitle->stopAction(forever_repeat_action);
	this->addChild(mainTitle);

	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(TWScene::onMouseUP, this); 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void TWScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void TWScene::onMouseUP(cocos2d::Event* event)
{
	auto mainTitle = this->getChildByName("MainTitle");
	if (!mainTitle->isVisible())
		mainTitle->setVisible(true);
	else
		mainTitle->setVisible(false);
}
