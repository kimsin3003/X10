#include "stdafx.h"
#include "StageScene.h"
#include "GameScene.h"
#include "UILayer.h"

StageScene::StageScene()
{
}


StageScene::~StageScene()
{
}

Scene* StageScene::CreateScene()
{
	Scene* scene = Scene::create();

	Layer* layer = StageScene::create();
	scene->addChild(layer);

	return scene;
}

bool StageScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}
	setName("StageScene");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//배경 그림 삽입.
	Layer* background = LoadBackground();
	this->addChild(background);

	/*back Button */
	MenuItemImage* pauseButton = MakeBackButton();
	Size buttonSize = pauseButton->getContentSize();
	pauseButton->setPosition(
		origin.x + visibleSize.width - buttonSize.width / 2,
		origin.y + buttonSize.height / 2
		);


	/*menu List : CCVector*/
	Vector<MenuItem*> menuList;
	menuList.pushBack(pauseButton);
	
	/*Create Menu*/
	auto menu = Menu::createWithArray(menuList);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

}

Layer* StageScene::LoadBackground()
{
	return nullptr;
}

void StageScene::MenuButtonCallback(Ref* pSender)
{
	ChangeToMainScene(pSender);
}

void StageScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameScene::createScene());
}

MenuItemImage* StageScene::MakeBackButton()
{
	MenuItemImage* button = MenuItemImage::create(
		"OrangePauseButton.png",
		"OrangePauseButton.png",
		CC_CALLBACK_1(StageScene::MenuButtonCallback, this));
	button->setScale(UILayer::PAUSE_BUTTON_WIDTH, UILayer::PAUSE_BUTTON_HEIGHT);
	
	return button;
}