#include "stdafx.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Sling.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto background = Sprite::create("res/x10bg.jpg");
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	background->setOpacity(140);
	scene->addChild(background);

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

	uiLayer = UILayer::create();
	gameLayer = GameLayer::create();
	this->addChild(uiLayer);
	this->addChild(gameLayer);
	
	GameManager::GetInstance()->InitTargets(gameLayer);

	this->scheduleUpdate();

	auto sling = Sling::GetInstance();
	this->addChild(sling);

	return true;
}

void GameScene::update(float dt){
	GameManager::GetInstance()->Play(gameLayer, uiLayer);
}