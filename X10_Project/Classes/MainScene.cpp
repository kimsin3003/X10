#include "stdafx.h"
#include "MainScene.h"
#include "MCScene.h"
#include "TWScene.h"
#include "JWScene.h"
#include "GameScene.h"
#include "Sling.h"
#include "GameManager.h"
#include "StageScene.h"

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = MainScene::create();

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

	/*Game start Button
	* 이건 최근 플레이 했던 탄이나, 최고 높은 탄으로 세팅되게 해놓는게 낫지 않을까?
	* 삭제 할라고 보니까 그게 날것 같어..
	*/
	auto startGame = MenuItemFont::create("START", CC_CALLBACK_1(MainScene::ChangeToGameScene, this));
	//set position center
	startGame->setPosition(	visibleSize.width / 2, 	visibleSize.height / 2);

	/*Stage Select Button*/
	auto stageSelect = MenuItemFont::create("Stage Select", CC_CALLBACK_1(MainScene::ChangeToStageScene, this));
	stageSelect->setScale(0.7);
	//set position center
	stageSelect->setPosition(visibleSize.width / 2, visibleSize.height / 2 - startGame->getContentSize().height);

	/* End Button */
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	/*Secret Paul's Test Page*/
	auto PaulItem = MenuItemFont::create("p", CC_CALLBACK_1(MainScene::ChangeToMCScene,this));
	PaulItem->setScale(0.5f);
	PaulItem->setPosition(Vec2(origin.x + visibleSize.width - PaulItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height + PaulItem->getContentSize().height/2));
	
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
	StageScene::GotoStage(pSender, 0);
}

void MainScene::ChangeToStageScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageScene::CreateScene());
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
