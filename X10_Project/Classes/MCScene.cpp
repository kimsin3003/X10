#include <string>
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
	GotoMainSceneMenu->setPosition(200, 300);
	this->addChild(GotoMainSceneMenu);

	auto taewooMission1 = Label::createWithTTF("JUMP!!!", "fonts/arial.ttf", 50);
	taewooMission1->setPosition(Point(200, 150));
	taewooMission1->setName("twMissionLabel");
	taewooMission1->setVisible(false);
	this->addChild(taewooMission1);

	auto dir = Director::getInstance();
	auto screen = dir->getVisibleSize();

	auto jinwookMission = Sprite::create("boy 31x40.png");
	auto boysize = jinwookMission->getContentSize();
	jinwookMission->setPosition(0 + boysize.width / 2, 0 + boysize.height / 2);
	jinwookMission->setName("boy");
	this->addChild(jinwookMission);

	auto moveToRL = MoveBy::create(1, Point(screen.width - boysize.width, 0));
	auto moveToRU = MoveBy::create(1, Point(0 , screen.height - boysize.height));
	auto moveToLU = MoveBy::create(1, Point( -screen.width + boysize.width, 0));
	auto moveToLL = MoveBy::create(1, Point(0, -screen.height + boysize.height));

	auto moveArround = Sequence::create(moveToRL, moveToRU, moveToLU, moveToLL, NULL);
	auto repeat_action = RepeatForever::create(moveArround);

	jinwookMission->runAction(repeat_action);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(MCScene::onMouseUp, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(MCScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	
	return true;
}

void MCScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void MCScene::onMouseUp(Event *event)
{
	auto label = this->getChildByName("twMissionLabel");
	label->setVisible(false);
}

void MCScene::onMouseDown(Event *event)
{
	auto e = (EventMouse*)event;
	auto blinkLabel = this->getChildByName("twMissionLabel");
	blinkLabel->setVisible(true);
	auto runningBoy = this->getChildByName("boy");
	auto moveToMouse = JumpBy::create(0.3, Point(0, 0), 50, 1);
	runningBoy->runAction(moveToMouse);
}