#include "stdafx.h"
#include "MainScene.h"
#include "GameScene.h"
#include "Sling.h"
#include "GameManager.h"
#include "StageScene.h"
#include "ConstVars.h"
#include "FileStuff.h"

#include "MapEditer.h"
#include <AudioEngine.h>
#include <SimpleAudioEngine.h>
#include "IntroScene.h"

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


	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 9);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(FileStuff::IMG_SOURCE);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_StreetLight = Sprite::create(FileStuff::GARO_OFF);
	m_StreetLight->setPosition(Vec2(visibleSize.width / 2 - 50 , visibleSize.height /2 ));
	m_StreetLight->setOpacity(40); //처음엔 가로등 어둡게
	m_StreetLightPos = m_StreetLight->getPosition();
	addChild(m_StreetLight);

	float selectedScale = 1.2;
	Point selectedAnchor = Point(selectedScale - 1.0, selectedScale - 1.0) / 2;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_MAIN_BACKGROUND, true);

	Vector<MenuItem*> menuItems;

	/*Game start Button*/
	MenuItemImage* startGame = MenuItemImage::create();

	startGame->setNormalImage(Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_STANDING)
		)
	);
	
	startGame->setSelectedImage(
		Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_SELECTED)
		)
	);

	startGame->setCallback(CC_CALLBACK_1(MainScene::ChangeToStageSceneEffect, this));
	startGame->setPosition(m_StreetLightPos + Vec2(100, -100));

	menuItems.pushBack(startGame); 

#ifdef _DEBUG
	/*MapEditer Button*/
 	MenuItemLabel* mapEditer = MenuItemLabel::create(Label::create("MapEditer", "res/NanumGothic.ttf", 20), 
		CC_CALLBACK_1(MainScene::ChangeToMapEditScene, this));

 	mapEditer->setPosition(visibleSize.width / 2, visibleSize.height - startGame->getContentSize().height - mapEditer->getContentSize().height);
 	menuItems.pushBack(mapEditer);
#else
	runAction(CallFunc::create(CC_CALLBACK_0(MainScene::SetDisplayStat, this, false)));
#endif

	/* End Button */
	MenuItemImage* closeItem = MenuItemImage::create(
		FileStuff::CLOSE_BUTTON,
		FileStuff::CLOSE_BUTTON,
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	float scale = 2.0f;
	closeItem->setScale(scale);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * scale / 2,
		closeItem->getContentSize().height * scale / 2));

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

void MainScene::SetDisplayStat(bool isOn)
{
	Director::getInstance()->setDisplayStats(isOn);
}

void MainScene::ChangeToStageScene(Ref* pSender)
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

void MainScene::ChangeToStageSceneEffect(Ref* pSender)
{
	Vec2 characterPosition = static_cast<MenuItemImage*>(pSender)->getPosition(); //없애기 전에 위치 저장해놓음
	removeChildByName("Buttons");
	
	//character 걸어가는 부분
	m_character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_HARDPIXEL);
	addChild(m_character, 2);

	m_character->setPosition(characterPosition);
	m_character->runAction(MoveTo::create(2.0f, m_StreetLight->getPosition() + Vec2(30, -45)));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_FOOTSTEP, false, 2.0f);

	//가로등 서서히 fadein 하는 부분
	m_StreetLight->runAction(FadeIn::create(2.5));

	Sequence* seq = Sequence::create(
		DelayTime::create(2.5f),
		CallFuncN::create(CC_CALLBACK_0(MainScene::BlinkStreetLight, this)),
		DelayTime::create(2.0f),
		CallFuncN::create(CC_CALLBACK_0(MainScene::TurnStreetLight, this)),
		DelayTime::create(2.0f),
		CallFuncN::create(CC_CALLBACK_1(MainScene::ChangeToStageScene, this)),
		nullptr);

	runAction(seq);
}

void MainScene::ChangeToMapEditScene(Ref* pSender)
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
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);
	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTWALKSTAGE, 0);
}

void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
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
	m_StreetLight->removeFromParent();
	m_StreetLight = Sprite::create(FileStuff::GARO_OFF);
	addChild(m_StreetLight);
	m_StreetLight->setPosition(m_StreetLightPos);
}

void MainScene::StreetLightOn()
{
	m_StreetLight->removeFromParent();
	m_StreetLight = Sprite::create(FileStuff::GARO_ON);
	addChild(m_StreetLight);
	m_StreetLight->setPosition(m_StreetLightPos);
}

void MainScene::TurnStreetLight()
{
	Sprite* light_beam = Sprite::create(FileStuff::LIGHT_BEAM);
	
	light_beam->setPosition(Vec2(3, -10));
	light_beam->setAnchorPoint(Vec2(0, 0));

	Sprite* fireWorks = Sprite::create(FileStuff::MAIN_BULLET);
	fireWorks->setPosition(35, 25);
	light_beam->addChild(fireWorks);

	m_StreetLight->addChild(light_beam, -1);
}