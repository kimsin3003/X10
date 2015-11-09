#include "stdafx.h"
#include "UILayer.h"
#include "MainScene.h"

UILayer* UILayer::createUILayer()
{
	UILayer* IU = UILayer::create();
	return IU;
}

bool UILayer::init()
{
	if (Layer::init() == false)
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* Pause Button */
	auto pauseButton = MenuItemImage::create(
		"OrangePauseButton.png",
		"OrangePauseButton.png",
		CC_CALLBACK_1(UILayer::menuButtonCallback, this));
	Size buttonSize = pauseButton->getContentSize();
	float scale = MIN(
		PAUSE_BUTTON_WIDTH / buttonSize.width,
		PAUSE_BUTTON_HEIGHT / buttonSize.height);
	pauseButton->setScale(scale);
	pauseButton->setPosition(Vec2(origin.x + visibleSize.width - (buttonSize*scale).width / 2,
		origin.y + (buttonSize*scale).height / 2));
	
	/*Create Menu*/
	auto menu = Menu::create(pauseButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void UILayer::menuButtonCallback(Ref* pSender)
{
	ChangeToMainScene(pSender);
}

void UILayer::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}
