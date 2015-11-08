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

	this->scheduleUpdate();
	return true;
}

void update(float dt){
	GameManager::GetInstance()->Play();
}