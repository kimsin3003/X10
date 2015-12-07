#include "stdafx.h"
#include "MainScene.h"
#include "StageScene.h"
#include "GameScene.h"
#include "UILayer.h"
#include "GameManager.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "CollectionManager.h"

Scene* StageScene::createScene()
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

	Sprite* background = LoadBackground();
	addChild(background);

	collectionManager = new CollectionManager();

	SetupButtons();
	SetupCollection();

	return true;
}

void StageScene::GotoStage(Ref* pSender, int stageNum)
{
	Scene* game = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(game->getChildByName("GameScene"));

	/*stage Information 불러오는 부분.*/
	GameManager::GetInstance()->SetStage(gameScene->GetGameLayer(), stageNum);

	Director::getInstance()->replaceScene(game);
}

void StageScene::SetupButtons()
{
	/*menu List : CCVector*/
	Vector<MenuItem*> menuList;

	/*back Button */
	MenuItemImage* pauseButton = MakeBackButton();
	Size buttonSize = pauseButton->getContentSize();
	menuList.pushBack(pauseButton);

	int advancedState = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);

	for (int i = 0; i <= advancedState; i++)
	{
		menuList.pushBack(MakeStageButton(i, 50 * (i + 1), 300));
	}

	/*Create Menu*/
	Menu* menu = Menu::createWithArray(menuList);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
}

void StageScene::SetupCollection()
{
	int advancedStage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);

	collectionManager->InitCollections(advancedStage);
	collectionManager->AppendCollectionToLayer(this);
}

Sprite* StageScene::LoadBackground()
{
	Sprite* background = Sprite::create(FileStuff::STAGESCENE_BACKGROUND);
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

MenuItemImage* StageScene::MakeBackButton()
{
	MenuItemImage* button = MenuItemImage::create(
		FileStuff::PAUSEBUTTON,
		FileStuff::PAUSEBUTTON,
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
	menuItem->setNormalImage(Sprite::create(FileStuff::STAR_OFF));
	menuItem->setSelectedImage(Sprite::create(FileStuff::STAR_ON));
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