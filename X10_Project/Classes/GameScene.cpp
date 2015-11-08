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
	this->scheduleUpdate();
}

void update(float dt){
	GameManager::GetInstance()->Play();
}