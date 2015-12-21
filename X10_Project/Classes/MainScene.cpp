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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float selectedScale = 1.2;
	Point selectedAnchor = Point(selectedScale - 1.0, selectedScale - 1.0) / 2;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		FileStuff::MAIN_BACKGROUND_SOUND, true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);

	/*Game start Button*/
	MenuItemImage* startGame = MenuItemImage::create(FileStuff::START_IMG, FileStuff::START_IMG, CC_CALLBACK_1(MainScene::ChangeToStageScene, this));
	startGame->setScale(4.0);
	startGame->getSelectedImage()->setAnchorPoint(selectedAnchor);
	startGame->getSelectedImage()->setScale(selectedScale);
	startGame->setPosition(visibleSize.width / 2, visibleSize.height / 2 + startGame->getContentSize().height * startGame->getScale());

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
	this->addChild(menu, 1);

	return true;
}

void MainScene::ChangeToStageScene(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::INITIAL_BACKGROUND_SOUND, true);
	Director::getInstance()->replaceScene(StageScene::createScene());
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
