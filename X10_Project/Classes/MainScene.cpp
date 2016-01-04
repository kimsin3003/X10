#include "stdafx.h"
#include "MainScene.h"
#include "MCScene.h"
#include "TWScene.h"
#include "JWScene.h"
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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(FileStuff::IMG_SOURCE);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_StreetLight = Sprite::create(FileStuff::GARO_OFF);
	m_StreetLight->setPosition(Vec2(visibleSize.width /2 , visibleSize.height /2));
	m_StreetLight->setOpacity(40); //처음엔 가로등 어둡게
	m_StreetLightPos = m_StreetLight->getPosition();
	addChild(m_StreetLight);

	float selectedScale = 1.2;
	Point selectedAnchor = Point(selectedScale - 1.0, selectedScale - 1.0) / 2;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		FileStuff::SOUND_MAIN_BACKGROUND, true);

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
	startGame->setPosition(m_StreetLightPos + Vec2(0, -100));

	menuItems.pushBack(startGame);
#ifdef _DEBUG
	/*MapEditer Button*/
	MenuItemLabel* mapEditer = MenuItemLabel::create(Label::create("MapEditer", "res/NanumGothic.ttf", 20), CC_CALLBACK_1(MainScene::ChangeToMapEditScene, this));
	mapEditer->setPosition(visibleSize.width / 2, visibleSize.height - startGame->getContentSize().height - mapEditer->getContentSize().height);


	menuItems.pushBack(mapEditer);

#else
	Action* action = CallFunc::create(CC_CALLBACK_0(MainScene::SetDisplayStat, this, false));
	runAction(action);

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


	auto paulScene = MenuItemImage::create(FileStuff::BLACKOUT, FileStuff::BLACKOUT, CC_CALLBACK_1(MainScene::ChangeToMCScene, this));
	paulScene->setScale(0.5f);
	paulScene->setPosition(320, 480);

	menuItems.pushBack(paulScene);

	auto jwScene = MenuItemImage::create(FileStuff::BLACKOUT, FileStuff::BLACKOUT, CC_CALLBACK_1(MainScene::ChangeToJWScene, this));
	jwScene->setScale(0.5f);
	paulScene->setPosition(320, 0);

	menuItems.pushBack(jwScene);


	auto menu = Menu::createWithArray(menuItems);
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
		Director::getInstance()->replaceScene(IntroScene::createScene());
	else
		Director::getInstance()->replaceScene(StageScene::createScene());
}

void MainScene::ChangeToStageSceneEffect(Ref* pSender)
{
	Vec2 characterPosition = static_cast<MenuItemImage*>(pSender)->getPosition(); //없애기 전에 위치 저장해놓음
	removeChildByName("Buttons");
	
	//character 걸어가는 부분
	m_character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_HARDPIXEL);
	addChild(m_character, 2);

	m_character->setPosition(characterPosition);
	m_character->runAction(MoveTo::create(2.0f, m_StreetLight->getPosition() + Vec2(9, -45)));
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

void MainScene::ChangeToMCScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MCScene::createScene());
}

void MainScene::ChangeToTWScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(TWScene::createScene());
}

void MainScene::ChangeToJWScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(JWScene::createScene());
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
	light_beam->setPosition(Vec2(3, -3));
	light_beam->setAnchorPoint(Vec2(0, 0));
	m_StreetLight->addChild(light_beam, -1);
}