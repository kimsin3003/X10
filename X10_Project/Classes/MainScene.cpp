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

	m_garo = Sprite::create(FileStuff::GARO_OFF);
	m_garo->setPosition(Vec2(110, 320));
	m_garoPos = m_garo->getPosition();
	addChild(m_garo);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float selectedScale = 1.2;
	Point selectedAnchor = Point(selectedScale - 1.0, selectedScale - 1.0) / 2;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		FileStuff::SOUND_MAIN_BACKGROUND, true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);

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

	startGame->setPosition(m_garoPos + Vec2(30, -200));

	/*MapEditer Button*/
	MenuItemLabel* mapEditer = MenuItemLabel::create(Label::create("MapEditer", "res/NanumGothic.ttf", 50), CC_CALLBACK_1(MainScene::ChangeToMapEditScene, this));
	mapEditer->setPosition(visibleSize.width / 2, visibleSize.height / 2 - startGame->getContentSize().height - mapEditer->getContentSize().height);

	/* End Button */
	MenuItemImage* closeItem = MenuItemImage::create(
		FileStuff::CLOSE_BUTTON,
		FileStuff::CLOSE_BUTTON,
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	float scale = 2.0f;
	closeItem->setScale(scale);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * scale / 2,
		closeItem->getContentSize().height * scale / 2));

	auto paulScene = MenuItemFont::create("WATCH ENDING", CC_CALLBACK_1(MainScene::ChangeToMCScene,this));
	paulScene->setScale(0.5f);
	paulScene->setPosition(Vec2(origin.x + visibleSize.width - paulScene->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height*scale + paulScene->getContentSize().height/2));
	
	auto twScene = MenuItemFont::create("TW", CC_CALLBACK_1(MainScene::ChangeToTWScene, this));
	twScene->setScaleX(0.5);
	twScene->setScaleY(0.5);
	twScene->setPosition(Point(200, 10));

	auto jwScene = MenuItemFont::create("RESET GAME", CC_CALLBACK_1(MainScene::ChangeToJWScene, this));
	jwScene->setScaleX(0.5);
	jwScene->setScaleY(0.5);
	jwScene->setPosition(Point(110, 10));

	auto menu = Menu::create(startGame, mapEditer, closeItem, twScene, paulScene, jwScene, NULL);
	menu->setPosition(Vec2::ZERO);
	menu->setName("Buttons");
	addChild(menu, 1);

	return true;
}

void MainScene::ChangeToStageScene(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_INITIAL_BACKGROUND, true);

	Director::getInstance()->replaceScene(StageScene::createScene());
}

void MainScene::ChangeToStageSceneEffect(Ref* pSender)
{
	removeChildByName("Buttons");

	m_character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_HARDPIXEL);
	addChild(m_character, 2);

	m_character->setPosition(m_garoPos + Vec2(30, -200));
	m_character->runAction(MoveTo::create(2.0f, m_garo->getPosition() + Vec2(9, -45)));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_FOOTSTEP, false, 2.0f);

	Sequence* seq = Sequence::create(
		DelayTime::create(2.5f),
		CallFuncN::create(CC_CALLBACK_0(MainScene::BlinkGaro, this)),
		DelayTime::create(2.0f),
		CallFuncN::create(CC_CALLBACK_0(MainScene::TurnGaro, this)),
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

void MainScene::BlinkGaro()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_STREETLIGHTS);

	CallFunc* garoOff =  CallFunc::create(CC_CALLBACK_0(MainScene::GaroOff, this));
	CallFunc* garoOn = CallFunc::create(CC_CALLBACK_0(MainScene::GaroOn, this));

	Sequence* seq =  Sequence::create(
		garoOn,
		DelayTime::create(0.25f),
		garoOff,
		DelayTime::create(1.0f),
		garoOn,
		DelayTime::create(0.2f),
		garoOff,
		DelayTime::create(0.2f),
		garoOn,
		nullptr);

	runAction(seq);
}

void MainScene::GaroOff()
{
	m_garo->removeFromParent();
	m_garo = Sprite::create(FileStuff::GARO_OFF);
	addChild(m_garo);
	m_garo->setPosition(m_garoPos);
}

void MainScene::GaroOn()
{
	m_garo->removeFromParent();
	m_garo = Sprite::create(FileStuff::GARO_ON);
	addChild(m_garo);
	m_garo->setPosition(m_garoPos);
}

void MainScene::TurnGaro()
{
	Sprite* light_beam = Sprite::create(FileStuff::LIGHT_BEAM);
	light_beam->setPosition(Vec2(3, -3));
	light_beam->setAnchorPoint(Vec2(0, 0));
	m_garo->addChild(light_beam, -1);
}