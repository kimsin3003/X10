#include "Scene4.h"
#include "ui/UIButton.h"
#include <iostream>
USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Scene * Scene4::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = Scene4::create();
	scene->addChild(layer);

	return scene;
}

bool Scene4::init()
{
	if(!Layer::init())
		return false;

	Size size = Director::getInstance()->getVisibleSize();
	Button* button = Button::create();
	button->setTitleText("Go to Scene 5");
	button->setPosition(Point(size.width / 2, size.height / 2));
	button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			Director::getInstance()->replaceScene(Scene5::createScene());
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

void Scene4::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

Scene4::Scene4()
{
}


Scene4::~Scene4()
{
}
