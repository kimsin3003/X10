#include "stdafx.h"
#include "MainScene.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "CreditScene.h"
#include "Sling.h"
#include "GameManager.h"
#include "StageScene.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "MapEditer.h"
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
	if (!Layer::init())
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

	/*Ending mode button*/
	MenuItemImage* setToEnding = MenuItemImage::create(FileStuff::BLACKOUT, FileStuff::WHITE,
		CC_CALLBACK_0(MainScene::SetToEnding, this));
	setToEnding->setScale(0.5f);
	setToEnding->setPosition(Vec2(0.0f, 0.0f));

	menuItems.pushBack(setToEnding);
	
	/*Intro mode button*/
	MenuItemImage* setToIntro = MenuItemImage::create(FileStuff::BLACKOUT, FileStuff::WHITE,
		CC_CALLBACK_0(MainScene::SetToIntro, this));
	setToIntro->setScale(0.5f);
	setToEnding->setPosition(Vec2(0.0f, 480.0f));

	menuItems.pushBack(setToIntro);

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
	
	light_beam->setFlipX(true);
	light_beam->setPosition(Vec2(-7.0f, -10.0f));
	light_beam->setAnchorPoint(Vec2(0, 0));

	Sprite* fireworks = Sprite::create(FileStuff::MAIN_BULLET);
	fireworks->setPosition(25, 20);
	light_beam->addChild(fireworks);

	m_streetLight->addChild(light_beam, -1);

	Sprite* title = Sprite::create(FileStuff::TITLE);
	title->setPosition(light_beam->getPosition() + Vec2(-100, +120));
	title->setScale(1.0f);
	
	light_beam->addChild(title);
}

void MainScene::ChangeToStageScene()
{
	int stageToPlay = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);

	if (stageToPlay == 0)
	{
		Director::getInstance()->replaceScene(IntroScene::createScene());
	}
	else
	{
		Director::getInstance()->replaceScene(StageScene::createScene());
	}
}

void MainScene::ChangeToMapEditScene()
{
	Director::getInstance()->replaceScene(MapEditer::createScene());
}

void MainScene::SetToEnding()
{
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 12);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTWALKSTAGE, 12);
}

void MainScene::SetToIntro()
{
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 0);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTWALKSTAGE, 0);
}

void MainScene::ExitGame()
{
	Director::getInstance()->end();
}

void MainScene::TurnOffDisplayStat()
{
	Director::getInstance()->setDisplayStats(false);
}
