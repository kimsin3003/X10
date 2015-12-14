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
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	setName("StageScene");

	m_stageToPlay = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);
	m_maxStageNum = StageInformation::GetMaxStageNum();

	if (m_stageToPlay == 0)
	{
		this->scheduleOnce(schedule_selector(StageScene::IntroEvent), 0.0f);
		return true;
	}

	Collection::m_isLooking = false;

	Sprite* background = LoadBackground();
	addChild(background);

	m_character = LoadCharacter();
	background->addChild(m_character);


	if (m_stageToPlay == m_maxStageNum) 
	{
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
	//Covetous Version
	/*
	PrintIntroPage(FileStuff::INTRO_01, 0.0f, 8.0f);
	PrintIntroPage(FileStuff::INTRO_02, 8.0f, 8.0f);
	PrintIntroPage(FileStuff::INTRO_03, 16.0f, 3.0f);
	PrintIntroPage(FileStuff::INTRO_04, 20.0f, 5.0f);
	
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);
	
	CallFuncN* callFuncN = CallFuncN::create(
		CC_CALLBACK_0(StageScene::GotoStage, this, 1));

	Sequence* seq = Sequence::create(
		DelayTime::create(25.0f),
		callFuncN,
		nullptr);

	runAction(seq);
	*/

	//FadeIn Version	
	Vec2 deltaPos = Vec2(0, 45.0f*1.75f);
	Vec2 textPos = Vec2(160.0f, 360.0f);

	PrintIntroText("By some kind of accident\nI forgot all of my memories", textPos, 0.0f, 3.0f);
	PrintIntroText("At that confusing moment\nin my head was just one\nquestion", textPos-=deltaPos, 4.5f, 3.0f);
	PrintIntroText("Why cant I stop doing this?", textPos-=deltaPos, 9.0f, 3.0f);
	PrintIntroText("SHOOTING UFOS\nWITH THESE\nFIRECRACKERS", textPos-=deltaPos, 13.0f, 1.0f);

	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);

	CallFuncN* callFuncN = CallFuncN::create(
		CC_CALLBACK_0(StageScene::GotoStage, this, 1));

	Sequence* seq = Sequence::create(
		DelayTime::create(18.0f),
		callFuncN,
		nullptr);

	runAction(seq);
}

void StageScene::PrintIntroPage(const string fileDir, float startTime, float keepTime)
{
	Sprite* page = Sprite::create(fileDir);
	page->setPosition(Vec2(160, 240));
	page->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	page->setScale(1.5f);
	page->setOpacity(0);
	addChild(page);

	Sequence* seq = Sequence::create(
		DelayTime::create(startTime),
		FadeIn::create(0.0f),
		DelayTime::create(keepTime),
		RemoveSelf::create(),
		nullptr);

	page->runAction(seq);
}

void StageScene::PrintIntroText(const string message, const Vec2 pos, float startTime, float keepTime)
{
	Label* text = Label::create(
		message, FileStuff::FONT_ARIAL, 12.5f);
	text->setAlignment(TextHAlignment::CENTER);
	text->setScale(1.75f);
	text->setOpacity(0);
	text->setAnchorPoint(Vec2(0.5, 0.5));
	text->setPosition(pos);
	addChild(text);


	Sequence* seq = Sequence::create(
		DelayTime::create(startTime),
		FadeIn::create(keepTime-1.0f),
		NULL);

	text->runAction(seq);
}

//Use Timeline System to coordinate Actions

//별자리가 솨아아아악 그림이 만들어진다
//별자리가 주인공의 머리속으로 들어온다 Take1

//번쩍번쩍번쩍 하얀 화면 검정 화면 Take2

//collection들이 하늘에 둥둥 떠다닌다 Take3 -> CM -> ForEndingSetting

//주인공 말풍성 : Yeah I now remember. She is not my lover. I robbed her and she killed herself   
//<- Method:CharacterDialogueBox(message, start time keep time) Take4

//컬렉션들에 대한 설명이 차례로 출력. 착각에서 진실로 cross fade -> C -> ForEndingSetting

//컬렉션이 모두 fade out 되고 Take5 
//남은 둥둥 떠다니는 그녀의 형상 - 그의 머리 속으로 그녀의 상처와 공포가 들어온다
//(빨간 화면, 핏방울 눈이 내린다) Take6

//He idled few moment, He dives into the sea, but some kind of power does not allow that. Take7

//He idled few moment, He recognizes he is to shot his head
//with these fireworks. (막대기를 바라본다) Take8

//He shot himself, several times suffering from shocks and flush flies. Take9

//Fade Out

//Intro 씬으로 전환 

void StageScene::EndingEvent(float dt)
{
	Take01(0.0f); // total 14
	Take02(14.0f); // total 8
}

//별자리가 솨아아아악 그림이 만들어진다
//별자리가 주인공의 머리속으로 들어온다
void StageScene::Take01(float startTime)
{
	Sprite* girl = Sprite::create(FileStuff::MOTHER);
	girl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	girl->setPosition(160, 350);
	girl->setOpacity(0);
	girl->setScale(1.5f);
	
	Sequence* seq = Sequence::create(
		DelayTime::create(startTime), // 0
		FadeIn::create(5.0f), // 5
		DelayTime::create(2.0f), // 2
		Spawn::create(
		FadeOut::create(3.0f),
//		Blink::create(3.0f, 10),
		MoveBy::create(3.0f, Vec2(0, -25)),
		nullptr), // 3

		ScaleTo::create(0.0f, 0.5f),
		Place::create(m_character->getPosition() + Vec2(175, 120)),
		FadeIn::create(1.0f),
		DelayTime::create(0.5f),
		
		Spawn::create(
		MoveBy::create(1.5f, Vec2(0, -75)),
		FadeOut::create(1.5f),
		nullptr), // 3
		
		RemoveSelf::create(),

		nullptr
		); // total : 14

	addChild(girl);
	girl->runAction(seq);
}

//번-쩍-- 번-쩍-- 번쩍번쩍번쩍번쩍번쩍---
void StageScene::Take02(float startTime)
{
	Sequence* seq = Sequence::create(
		DelayTime::create(startTime),
		CreateSpark(0.50f, 0.45f, 3), // 3
		CreateSpark(0.20f, 0.25f, 5), // 3
		CreateSpark(0.15f, 0.10f, 6), // 1
		CreateSpark(0.07f, 0.06f, 8), // 1
		//sound effect
		nullptr);

	runAction(seq);
}

Repeat* StageScene::CreateSpark(float blackTime, float whiteTime, int repeatTime)
{
	Sequence* low = Sequence::create(
		TintTo::create(0.0f, Color3B::BLACK),
		DelayTime::create(blackTime),
		TintTo::create(0.0f, Color3B::WHITE),
		DelayTime::create(whiteTime),
		nullptr
		);

	return Repeat::create(low, repeatTime);
}

void StageScene::Take03(float startTime)
{

}

void StageScene::Take04(float startTime)
{

}

void StageScene::Take05(float startTime)
{

}

void StageScene::Take06(float startTime)
{

}

void StageScene::Take07(float startTime)
{

}

void StageScene::Take08(float startTime)
{

}

void StageScene::Take09(float startTime)
{

}

void StageScene::Take10(float startTime)
{

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
	int lastStage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);

	if (stageNum == lastStage)
	{
		menuItem->setNormalImage(Sprite::create(FileStuff::TOGO_STAR));
	}
	else if (stageNum == CollectionManager::SHOES ||
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
	//menuItem->getSelectedImage()->setAnchorPoint(Point(0.2, 0.2));
	menuItem->setCallback(CC_CALLBACK_0(StageScene::GotoStage, this, stageNum));
	menuItem->setPosition(pos);

	//char str[10];
	//sprintf(str, "Stage %d", stageNum);
	//Label* stageText = Label::create(str, "Consolas", 10);
	//menuItem->addChild(stageText);
	//stageText->setPosition(Point(0, -10));
	
	return menuItem;
}
