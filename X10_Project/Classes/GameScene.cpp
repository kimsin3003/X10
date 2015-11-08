#include "stdafx.h"
#include "GameScene.h"
#include "GameManager.h"


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

	gameLayer = GameLayer::create();
	GameManager::GetInstance()->InitTargets(gameLayer);

	uiLayer = UILayer::create();
	this->addChild(gameLayer);
	this->addChild(uiLayer);
	this->scheduleUpdate();

	auto sling = Sling::GetInstance();
	this->addChild(sling);

	return true;
}

void GameScene::update(float dt){
	GameManager::GetInstance()->Play(gameLayer);
}