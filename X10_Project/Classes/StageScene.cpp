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
//etc
#include "Collection.h"

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
	if (!Layer::init())
	{
		return false;
	}

	setName("StageScene");

	m_stageToPlay = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);
	m_maxStageNum = StageInformation::GetMaxStageNum();

	Collection::m_isLooking = false;

	Sprite* background = LoadBackground();
	addChild(background);

	m_character = LoadCharacter();
	background->addChild(m_character);

	if (m_stageToPlay == 0)
	{
		this->scheduleOnce(schedule_selector(StageScene::IntroEvent), 0.0f);
		return true;
	}

	if (m_stageToPlay == m_maxStageNum) 
	{
		Sprite* mother = Sprite::create(FileStuff::MOTHER);
		mother->setAnchorPoint(Vec2::ZERO);
		mother->setPosition(20, 250);
		mother->setScale(1.5f);
		addChild(mother);

		this->scheduleOnce(schedule_selector(StageScene::EndingEvent), 1.5f);

		return true;
	}

	m_collectionManager = new CollectionManager();
	m_stageButtonPosInfo = new StageButtonPosInformation();

	SetupButtons();
	SetupCollection();

	return true;
}

void StageScene::SetupButtons()
{
	Vector<MenuItem*> menuList;

	MenuItemImage* pauseButton = MakeBackButton();

	menuList.pushBack(pauseButton);

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
	m_collectionManager->InitCollections(m_stageToPlay-1);
	m_collectionManager->AppendCollectionToLayer(this);
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

void StageScene::GotoStage(Ref* pSender, int stageNum)
{
	Scene* scene = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(scene->getChildByName("GameScene"));

	GameManager::GetInstance()->SetStage(gameScene->GetGameLayer(), stageNum);
	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);

	Director::getInstance()->replaceScene(sceneWithEffect);
}

void StageScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void StageScene::IntroEvent(float dt)
{
	float fadeInTime = 2.0f;
	float delayTime = 3.0f;

	Vec2 deltaPos = Vec2(0, 16.0f);
	Vec2 textPos = Vec2(160.0f, 320.0f);

	//0.0f~
	Label* text_00 = Label::create(
		"It seems that I forgot all memories by some kind of accident.", 
		FileStuff::FONT_ARIAL, 12.5f);
	text_00->setOpacity(10);
	text_00->setAnchorPoint(Vec2(0.5, 0.5));
	text_00->setPosition(textPos);
	addChild(text_00);

	FadeIn* fadeIn_00 = FadeIn::create(fadeInTime);

	text_00->runAction(fadeIn_00);

	//1.0f~
	Label* text_01 = Label::create(
		"In my head was just this question at that confusing moment.", 
		FileStuff::FONT_ARIAL, 12.5f);
	text_01->setOpacity(10);
	text_01->setAnchorPoint(Vec2(0.5, 0.5));
	text_01->setPosition(textPos -= deltaPos);
	addChild(text_01);

	Sequence* seq_01 = Sequence::create(
		DelayTime::create(delayTime += fadeInTime),
		FadeIn::create(fadeInTime),
		nullptr);

	text_01->runAction(seq_01);

	//2.0f~
	Label* text_02 = Label::create(
		"Why cant I stop doing this?", 
		FileStuff::FONT_ARIAL, 12.5f);
	text_02->setOpacity(10);
	text_02->setAnchorPoint(Vec2(0.5, 0.5));
	text_02->setPosition(textPos -= deltaPos);
	addChild(text_02);

	Sequence* seq_02 = Sequence::create(
		DelayTime::create(delayTime += fadeInTime+1.0f),
		FadeIn::create(fadeInTime),
		nullptr);

	text_02->runAction(seq_02);

	//3.0f~
	Label* text_03 = Label::create(
		"SHOOTING UFOS", 
		FileStuff::FONT_ARIAL, 15.5f);
	text_03->setAnchorPoint(Vec2(0.5, 0.5));
	text_03->setPosition(textPos -= deltaPos);
	text_03->setOpacity(10);
	addChild(text_03);

	Sequence* seq_03 = Sequence::create(
		DelayTime::create(delayTime += fadeInTime+2.0f),
		FadeIn::create(0.0f),
		NULL);

	text_03->runAction(seq_03);

	Label* text_04 = Label::create(
		"WITH MOTHERFUCKING FIRECRACKERS",
		FileStuff::FONT_ARIAL, 15.5f);
	text_04->setAnchorPoint(Vec2(0.5, 0.5));
	text_04->setPosition(textPos -= deltaPos);
	text_04->setOpacity(10);
	addChild(text_04);

	Sequence* seq_04 = Sequence::create(
		DelayTime::create(delayTime),
		FadeIn::create(0.0f),
		NULL);

	text_04->runAction(seq_04);
	//sprite

	//5.0f~
//	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);
//	GotoStage(this, 1);
}

void StageScene::EndingEvent(float dt)
{
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 0);
	TransitionRotoZoom* byebye = TransitionRotoZoom::create(2.0f, MainScene::createScene());
	Director::getInstance()->replaceScene(byebye);
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
		menuItem->setScale(1.25f);
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
