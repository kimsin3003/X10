#include "stdafx.h"
#include "MainScene.h"
#include "TutorialScene.h"
#include "GameScene.h"
#include "CreditScene.h"
#include "Sling.h"
#include "GameManager.h"
#include "IntroScene.h"
#include "StageScene.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "MapEditer.h"
#include "AdmobHelper.h"
#include <AudioEngine.h>
#include <SimpleAudioEngine.h>

Scene* MainScene::createScene()
{
    Scene* scene = Scene::create();
    
    MainScene* layer = MainScene::create();
	
    scene->addChild(layer);

    return scene;
}

bool MainScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,0)))
	{
		return false;
	}

	setPosition(0, -20);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_MAIN_BACKGROUND, true);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(FileStuff::IMG_SOURCE);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_streetLight = Sprite::create(FileStuff::GARO_OFF);
	m_streetLight->setPosition(Vec2(260, 360));
	m_streetLight->setOpacity(40);
	m_streetLight->setFlipX(true);
	m_streetLight->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_StreetLightPos = m_streetLight->getPosition();
	addChild(m_streetLight);

	Vector<MenuItem*> menuItems;

	if ( UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE) > 1 ){
		MenuItemImage* resetGameButton = MenuItemImage::create(FileStuff::RESET_GAME, FileStuff::RESET_GAME);
		resetGameButton->setCallback(CC_CALLBACK_0(MainScene::ResetGame, this));
		resetGameButton->setPosition(230, 180);
		resetGameButton->setScale(0.55f);
		resetGameButton->setAnchorPoint(Vec2(0.5f, 0.5f));

		menuItems.pushBack(resetGameButton);

		MenuItemImage* tutorialButton = MenuItemImage::create(FileStuff::TUTORIAL, FileStuff::TUTORIAL);
		tutorialButton->setCallback(CC_CALLBACK_0(MainScene::ChangeToTutorialScene, this));
		tutorialButton->setPosition(230, 140);
		tutorialButton->setScale(0.6f);
		tutorialButton->setAnchorPoint(Vec2(0.5f, 0.5f));

		menuItems.pushBack(tutorialButton);

	}

	if (UserDefault::getInstance()->getBoolForKey(ConstVars::CLEARED_ONCE, false)){

		MenuItemImage* creditGameButton = MenuItemImage::create(FileStuff::CREDIT, FileStuff::CREDIT);
		creditGameButton->setCallback(CC_CALLBACK_0(MainScene::ChangeToCreditScene, this));
		creditGameButton->setPosition(230, 100);
		creditGameButton->setScale(0.6f);
		creditGameButton->setAnchorPoint(Vec2(0.5f, 0.5f));

		menuItems.pushBack(creditGameButton);
	}

	MenuItemImage* clickMe = MenuItemImage::create(FileStuff::CLICK_ME, FileStuff::CLICK_ME);
	clickMe->setPosition(90, 190);
	clickMe->setScale(0.8);
	clickMe->setAnchorPoint(Vec2(0.5f, 0.5f));

	menuItems.pushBack(clickMe);

	/*Character*/
	MenuItemImage* character = MenuItemImage::create();

	character->setNormalImage(
		Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_CACHE)
		));
	
	character->setSelectedImage(
		Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_SELECTED)
		)
	);

	character->setCallback(CC_CALLBACK_0(MainScene::WalkToStreetLight, this));
	character->setPosition(80, 120);
	character->setAnchorPoint(Vec2(0.5f, 0.5f));

	menuItems.pushBack(character); 

#ifdef _DEBUG
//	/* MapEditer Button */
// 	MenuItemLabel* mapEditer = MenuItemLabel::create(Label::create("MapEditer", "res/NanumGothic.ttf", 20), 
//		CC_CALLBACK_0(MainScene::ChangeToMapEditScene, this));
//
//  	mapEditer->setPosition(visibleSize.width / 2, visibleSize.height - character->getContentSize().height - mapEditer->getContentSize().height);
//  	menuItems.pushBack(mapEditer);

	/*Ending mode button*/
	MenuItemImage* setToEnding = MenuItemImage::create(FileStuff::BLACKOUT, FileStuff::WHITE,
		CC_CALLBACK_0(MainScene::SetToEnding, this));
	setToEnding->setScale(0.5f);
	setToEnding->setPosition(Vec2(0.0f, 480.0f));

	menuItems.pushBack(setToEnding);

	/*Intro mode button*/
	MenuItemImage* setToIntro = MenuItemImage::create(FileStuff::BLACKOUT, FileStuff::WHITE,
		CC_CALLBACK_0(MainScene::SetToIntro, this));
	setToIntro->setScale(0.5f);
	setToIntro->setPosition(Vec2(0.0f, 0.0f));

	menuItems.pushBack(setToIntro);

#else
	runAction(CallFunc::create(CC_CALLBACK_0(MainScene::TurnOffDisplayStat, this)));
#endif

	/* End Button */
	MenuItemImage* closeItem = MenuItemImage::create(
		FileStuff::CLOSE_BUTTON,
		FileStuff::CLOSE_BUTTON,
		CC_CALLBACK_0(MainScene::ExitGame, this));
	float scale = 2.0f;
	closeItem->setScale(scale);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * scale / 2,
		closeItem->getContentSize().height * scale / 2) + Vec2(0, 20));

	menuItems.pushBack(closeItem);

	Menu* menu = Menu::createWithArray(menuItems);
	menu->setPosition(Vec2::ZERO);
	menu->setName("Buttons");
	addChild(menu, 1);

	return true;
}

void MainScene::WalkToStreetLight()
{
	removeChildByName("Buttons");

	m_character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_CACHE);
	addChild(m_character, 2);

	m_character->setPosition(80, 120);
	m_character->runAction(MoveTo::create(2.5f, m_streetLight->getPosition() + Vec2(-40, -45)));

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_FOOTSTEP, false, 2.0f);

	m_streetLight->runAction(FadeIn::create(3.0f));

	Sequence* seq = Sequence::create(
		DelayTime::create(3.5f),
		CallFuncN::create(CC_CALLBACK_0(MainScene::BlinkStreetLight, this)),
		DelayTime::create(3.0f),
		CallFuncN::create(CC_CALLBACK_0(MainScene::BrightenStreetLight, this)),
		DelayTime::create(4.0f),
		CallFuncN::create(CC_CALLBACK_0(MainScene::ChangeToStageScene, this)),
		nullptr);

	runAction(seq);
}

void MainScene::BlinkStreetLight()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_STREETLIGHTS);

	CallFunc* StreetLightOff =  CallFunc::create(CC_CALLBACK_0(MainScene::StreetLightOff, this));
	CallFunc* StreetLightOn = CallFunc::create(CC_CALLBACK_0(MainScene::StreetLightOn, this));

	Sequence* seq =  Sequence::create(
		StreetLightOn,
		DelayTime::create(0.25f),
		StreetLightOff,
		DelayTime::create(1.0f),
		StreetLightOn,
		DelayTime::create(0.2f),
		StreetLightOff,
		DelayTime::create(0.2f),
		StreetLightOn,
		nullptr);

	runAction(seq);
}

void MainScene::StreetLightOff()
{
	m_streetLight->removeFromParent();
	m_streetLight = Sprite::create(FileStuff::GARO_OFF);
	m_streetLight->setFlipX(true);
	addChild(m_streetLight);
	m_streetLight->setPosition(m_StreetLightPos);
}

void MainScene::StreetLightOn()
{
	m_streetLight->removeFromParent();
	m_streetLight = Sprite::create(FileStuff::GARO_ON);
	m_streetLight->setFlipX(true);
	addChild(m_streetLight);
	m_streetLight->setPosition(m_StreetLightPos);
}

void MainScene::BrightenStreetLight()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_LIGHT_ON);

	Sprite* light_beam = Sprite::create(FileStuff::LIGHT_BEAM);

	light_beam->setFlippedX(true);
	light_beam->setPosition(Vec2(-7.0f, -10.0f));
	light_beam->setAnchorPoint(Vec2(0, 0));

	m_streetLight->addChild(light_beam, -1);
	
	Sprite* fireworks = Sprite::create(FileStuff::MAIN_BULLET);
	fireworks->setPosition(Vec2(25.0f, 20.0f));
	light_beam->addChild(fireworks);
	
	Sprite* title = Sprite::create(FileStuff::TITLE);
	title->setPosition(Vec2(-100.0f, +120.0f));
	light_beam->addChild(title);
}

void MainScene::ChangeToCreditScene()
{
	Director::getInstance()->replaceScene(CreditScene::createScene());
}

void MainScene::ChangeToStageScene()
{
	if (UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTWALKSTAGE, 0) > 0)
		Director::getInstance()->replaceScene(StageScene::createScene());
	else
		Director::getInstance()->replaceScene(IntroScene::createScene());
}

void MainScene::ChangeToTutorialScene()
{
	Director::getInstance()->pushScene(TutorialScene::createScene());
}

void MainScene::ChangeToMapEditScene()
{
	Director::getInstance()->replaceScene(MapEditer::createScene());
}


void MainScene::SetToIntro()
{
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTWALKSTAGE, 0);
	UserDefault::getInstance()->setBoolForKey(ConstVars::CLEARED_ONCE, false);
}


void MainScene::SetToEnding()
{
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 12);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTWALKSTAGE, 11);
	UserDefault::getInstance()->setBoolForKey(ConstVars::CLEARED_ONCE, false);
}

void MainScene::ResetGame()
{
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTWALKSTAGE, 0);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::FAIL_COUNT, 0);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::PLAY_COUNT, 0);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::THIS_PLAY_TIME, 0);
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void MainScene::ExitGame()
{
	Director::getInstance()->end();
}

void MainScene::TurnOffDisplayStat()
{
	Director::getInstance()->setDisplayStats(false);
}

void MainScene::PlayAd()
{
	if (AdmobHelper::isAdShowing)
		AdmobHelper::hideAd();
	else
		AdmobHelper::showAd();
}
