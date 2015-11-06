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
	if (!CCLayerColor::initWithColor(Color4B::BLUE))
	{
		return false;
	}

	ParticleFireworks* fireworks = ParticleFireworks::create();
	this->addChild(fireworks);

	return true;
}

void TWScene::ChangeBackground(float deltaTIme)
{
	Color3B color;
	int rand = random() % 5;
	switch (rand){
	case 0:  
		color = Color3B::YELLOW;
		break;
	case 1:
		color = Color3B::BLUE;
		break;
	case 2:
		color = Color3B::GREEN;
		break;
	case 3:
		color = Color3B::RED;
		break;
	case 4:
		color = Color3B::MAGENTA;
		break;
	case 5:
		color = Color3B::BLACK;
		break;
	case 6:
		color = Color3B::ORANGE;
		break;
	case 7:
		color = Color3B::GRAY;
		break;
	}
	this->setColor(color);
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
