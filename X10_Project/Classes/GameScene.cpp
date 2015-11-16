#include "stdafx.h"
#include "GameScene.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "Sling.h"

GameScene::GameScene() : gameLayer(nullptr), uiLayer(nullptr)
{
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer);
	
	return scene;
}

bool GameScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}
	setName("GameScene");

	//배경 그림 삽입.
	auto background = loadBackground();
	this->addChild(background);

	//레이어 삽입
	gameLayer = GameLayer::create();
	uiLayer = UILayer::create();
	this->addChild(gameLayer);
	this->addChild(uiLayer);
	

	/*stage Information 불러오는 부분.*/
	int stageNum = 0; //임시 스테이지 번호.
	GameManager::GetInstance()->SetStage(gameLayer, stageNum);
	
	this->scheduleUpdate();

	return true;
}

Sprite* GameScene::loadBackground()
{
	auto background = Sprite::create(BOTTOM_BGIMG_FILE);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	background->setOpacity(140);
	return background;
}

void GameScene::update(float dt)
{
	GameManager::GetInstance()->Play(gameLayer, uiLayer);
}