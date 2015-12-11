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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	float selectedScale = 1.2;
	Point selectedAnchor = Point(selectedScale - 1.0, selectedScale - 1.0) / 2;
	/*Game start Button*/
	MenuItemImage* startGame = MenuItemImage::create(FileStuff::START_IMG, FileStuff::START_IMG, CC_CALLBACK_1(MainScene::ChangeToGameScene, this));
	startGame->setScale(4.0);
	startGame->getSelectedImage()->setAnchorPoint(selectedAnchor);
	startGame->getSelectedImage()->setScale(selectedScale);
	startGame->setPosition(visibleSize.width / 2, visibleSize.height / 2 + startGame->getContentSize().height * startGame->getScale());

	/*Stage Select Button*/
	MenuItemImage* stageSelect = MenuItemImage::create(FileStuff::STAGE_SELECT_IMG, FileStuff::STAGE_SELECT_IMG, CC_CALLBACK_1(MainScene::ChangeToStageScene, this));
	stageSelect->setScale(2.0);
	stageSelect->getSelectedImage()->setAnchorPoint(selectedAnchor);
	stageSelect->getSelectedImage()->setScale(selectedScale);
	stageSelect->setPosition(visibleSize.width / 2, visibleSize.height / 2 - startGame->getContentSize().height);

	/* End Button */
	MenuItemImage* closeItem = MenuItemImage::create(
		FileStuff::CLOSE_BUTTON,
		FileStuff::CLOSE_BUTTON,
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	float scale = 2.0f;
	closeItem->setScale(scale);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * scale / 2,
		closeItem->getContentSize().height * scale / 2));

	/*Secret Paul's Test Page*/
	auto PaulItem = MenuItemFont::create("p", CC_CALLBACK_1(MainScene::ChangeToMCScene,this));
	PaulItem->setScale(0.5f);
	PaulItem->setPosition(Vec2(origin.x + visibleSize.width - PaulItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height*scale + PaulItem->getContentSize().height/2));
	
	/*Secret Tw's Test Page*/
	auto twScene = MenuItemFont::create("TW_SecretButton", CC_CALLBACK_1(MainScene::GoToTW, this));
	twScene->setScaleX(0.5);
	twScene->setScaleY(0.5);
	twScene->setPosition(Point(200, 10));

	/*Secret Jw's Test Page*/
	auto jwScene = MenuItemFont::create("jwwj", CC_CALLBACK_1(MainScene::ChangeToJWScene, this));
	jwScene->setScaleX(0.5);
	jwScene->setScaleY(0.5);
	jwScene->setPosition(Point(110, 10));

	/*Create Menu*/
	auto menu = Menu::create(startGame, stageSelect, closeItem, twScene, PaulItem, jwScene, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void MainScene::ChangeToGameScene(Ref* pSender)
{
	StageScene::GotoStage(pSender, UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE));
}

void MainScene::ChangeToStageScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageScene::createScene());
}

void MainScene::ChangeToMCScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MCScene::createScene());
}

void MainScene::GoToTW(Ref* pSender)
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
