#include "stdafx.h"
//scene
#include "StageScene.h"
#include "MainScene.h"
#include "GameScene.h"
//layer
#include "UILayer.h"
//info
#include "StageButtonPosInformation.h"
#include "StageInformation.h"
//manager
#include "CollectionManager.h"
#include "GameManager.h"
//config
#include "ConstVars.h"
#include "FileStuff.h"

Scene* StageScene::createScene()
{
	Scene* scene = Scene::create();
	scene->setAnchorPoint(Vec2::ZERO);
	scene->setPosition(Vec2::ZERO);

	Layer* layer = StageScene::create();
	layer->setAnchorPoint(Vec2::ZERO);
	layer->setPosition(Vec2::ZERO);

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

	m_character = LoadCharacter();
	background->addChild(m_character);

	if (m_stageToPlay == m_maxStageNum) 
	{
		Sprite* mother = Sprite::create(FileStuff::MOTHER);
		mother->setAnchorPoint(Vec2::ZERO);
		mother->setPosition(20, 250);
		mother->setScale(1.5f);
		addChild(mother);
	}

	m_collectionManager = new CollectionManager();
	m_stageButtonPosInfo = new StageButtonPosInformation();

	m_stageToPlay = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);
	m_maxStageNum = StageInformation::GetMaxStageNum();

	SetupButtons();
	SetupCollection();

	return true;
}

void StageScene::SetupButtons()
{
	Vector<MenuItem*> menuList;

	MenuItemImage* pauseButton = MakeBackButton();
	Size buttonSize = pauseButton->getContentSize();
	menuList.pushBack(pauseButton);

	if (m_stageToPlay > m_maxStageNum)
	{
		m_stageToPlay = m_maxStageNum;
	}

	for (int i = 1; i <= m_stageToPlay; i++)
	{
		menuList.pushBack(MakeStageButton(i, m_stageButtonPosInfo->GetStageButtonPos(i)));
	}

	Menu* menu = Menu::createWithArray(menuList);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
}

void StageScene::SetupCollection()
{
	m_collectionManager->InitCollections(m_stageToPlay);
	m_collectionManager->AppendCollectionToLayer(this);
}

void StageScene::GotoStage(Ref* pSender, int stageNum)
{
	Scene* game = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(game->getChildByName("GameScene"));

	int maxStageNum = StageInformation::GetMaxStageNum();
	if (stageNum > maxStageNum)
	{
		stageNum = maxStageNum;
	}

	GameManager::GetInstance()->SetStage(gameScene->GetGameLayer(), stageNum);

	Director::getInstance()->replaceScene(game);
}

Sprite* StageScene::LoadBackground()
{
	Sprite* background = Sprite::create(FileStuff::BACKGROUND);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	background->setOpacity(140);

	return background;
}

Sprite* StageScene::LoadCharacter()
{
	Sprite* character = Sprite::create(FileStuff::CHARACTER_STANDING);
	character->setPosition(40, 12);
	character->setScale(0.3f);

	return character;
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
		CC_CALLBACK_1(StageScene::ChangeToMainScene, this));

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

MenuItemImage* StageScene::MakeStageButton(int stageNum, Point pos)
{
	MenuItemImage* menuItem = MenuItemImage::create();

	if (stageNum == CollectionManager::SHOES ||
		stageNum == CollectionManager::SCARF ||
		stageNum == CollectionManager::BOTTLE ||
		stageNum == CollectionManager::MONITOR ||
		stageNum == CollectionManager::LETTER ||
		stageNum == m_maxStageNum)
	{
		menuItem->setNormalImage(Sprite::create(FileStuff::SPECIAL_STAR));
	}
	else
	{
		menuItem->setNormalImage(Sprite::create(FileStuff::NORMAL_STAR));
	}
	menuItem->setSelectedImage(Sprite::create(FileStuff::STAR_ON));
	menuItem->getSelectedImage()->setAnchorPoint(Point(0.2, 0.2));
	menuItem->setCallback(CC_CALLBACK_0(StageScene::GotoStage, this, stageNum));
	menuItem->setPosition(pos);

	//char str[10];
	//sprintf(str, "Stage %d", stageNum);
	//Label* stageText = Label::create(str, "Consolas", 10);
	//menuItem->addChild(stageText);
	//stageText->setPosition(Point(0, -10));
	
	return menuItem;
}
