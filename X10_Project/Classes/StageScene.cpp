#include "stdafx.h"
#include "MainScene.h"
#include "StageScene.h"
#include "GameScene.h"
#include "UILayer.h"
#include "GameManager.h"

StageScene::StageScene() {}
StageScene::~StageScene() {}

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

	//배경 그림 삽입.
	Sprite* background = LoadBackground();
	this->addChild(background);

	/*menu List : CCVector*/
	Vector<MenuItem*> menuList;

	/*back Button */
	MenuItemImage* pauseButton = MakeBackButton();
	Size buttonSize = pauseButton->getContentSize();
	menuList.pushBack(pauseButton);
	
	/*Test Stage*/
	MenuItemImage* stage0 = MakeStageButton(0, 100, 300);
	menuList.pushBack(stage0);

	/*Paul's Stage*/
	MenuItemImage* stage3 = MakeStageButton(3, 300, 400);
	menuList.pushBack(stage3);

	/*TW's stage*/
	MenuItemImage* stage1 = MakeStageButton(1, 200, 400);
	menuList.pushBack(stage1);

	/*JW's stage*/
	MenuItemImage* stage2 = MakeStageButton(2, 300, 300);
	menuList.pushBack(stage2);

	/*Create Menu*/
	auto menu = Menu::createWithArray(menuList);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	///# 리턴값 어디갔노?

}

Sprite* StageScene::LoadBackground()
{
	auto background = Sprite::create(BGIMG_FILE);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	background->setOpacity(140);
	return background;
}

void StageScene::MenuButtonCallback(Ref* pSender)
{
	ChangeToMainScene(pSender);
}

void StageScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void StageScene::GotoStage(Ref* pSender, int stageNum)
{
	Scene* game = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(game->getChildByName("GameScene"));
	/*stage Information 불러오는 부분.*/
	GameManager::GetInstance()->SetStage(gameScene->GetGameLayer(), stageNum);

	Director::getInstance()->replaceScene(game);
}

MenuItemImage* StageScene::MakeBackButton()
{
	MenuItemImage* button = MenuItemImage::create(
		"OrangePauseButton.png",
		"OrangePauseButton.png",
		CC_CALLBACK_1(StageScene::MenuButtonCallback, this));
	Size buttonSize = button->getContentSize();
	float scale = MIN(
		UILayer::PAUSE_BUTTON_WIDTH / buttonSize.width,
		UILayer::PAUSE_BUTTON_HEIGHT / buttonSize.height);
	button->setScale(scale);
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	button->setPosition(
		origin.x + visibleSize.width - buttonSize.width*scale / 2,
		origin.y + buttonSize.height*scale / 2
		);

	return button;
}

MenuItemImage* StageScene::MakeStageButton(int stage, float xPos, float yPos)
{
	MenuItemImage* menuItem = MenuItemImage::create();
	menuItem->setNormalImage(Sprite::create("res/star.png"));
	menuItem->setSelectedImage(Sprite::create("res/star_twinkle.png"));
	menuItem->getSelectedImage()->setAnchorPoint(Point(0.2,0.2));
	menuItem->setCallback(CC_CALLBACK_0(StageScene::GotoStage, this, stage));
	menuItem->setPosition(xPos, yPos);
	char str[10];
	sprintf(str, "Stage %d", stage);
	Label* stageText = Label::create(str, "Consolas", 10);
	menuItem->addChild(stageText);
	stageText->setPosition(Point(0, -10));
	return menuItem;
}