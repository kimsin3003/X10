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
	if (!Layer::init())
		return false;
	gameLayer = GameLayer::create();
	uiLayer = UILayer::create();
	this->addChild(gameLayer);
	this->addChild(uiLayer);
	this->scheduleUpdate();

	return true;
}

void GameScene::update(float dt){
	GameManager::GetInstance()->Play(gameLayer);
}