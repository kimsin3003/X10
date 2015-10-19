#include "MainScene.h"
#include "HelloWorldScene.h"
#include "ui/UIButton.h"
#include <iostream>
USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Scene * MainScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if(!Layer::init())
		return false;

	Size size = Director::getInstance()->getVisibleSize();
	Button* button = Button::create();
	button->setTitleText("Start Game");
	button->setPosition(Point(size.width / 2, size.height / 2));
	button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			Director::getInstance()->replaceScene(HelloWorld::createScene());
			break;
		case ui::Widget::TouchEventType::ENDED:
			std::cout << "Button 1 clicked" << std::endl;
			break;
		default:
			break;
		}
	});

	this->addChild(button);
	return true;
}

void MainScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}
