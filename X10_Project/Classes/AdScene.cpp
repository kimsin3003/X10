#include "stdafx.h"
#include "AdScene.h"
#include "AdmobHelper.h"
#include "GameScene.h"
#include "GameManager.h"

Scene* AdScene::createScene()
{
	Scene* scene = Scene::create();

	Layer* layer = AdScene::create();
	scene->addChild(layer);

	return scene;
}

bool AdScene::init(){

	if (!Layer::init())
	{
		return false;
	}

	//setColor(Color3B(30, 30, 40)); //change gray color

	Label* waitLabel = Label::create("It's Ad time.", "arial", 24);
	Director* dir = Director::getInstance();
	float width = dir->getVisibleSize().width;
	float height = dir->getVisibleSize().height;
	waitLabel->setPosition(Vec2(width / 2, height / 2));
	addChild(waitLabel);

	//PlayAd();
	
	lifeTime = 3.0;
	scheduleUpdate();
}

void AdScene::PlayAd()
{
	AdmobHelper::showAd();
}

void AdScene::ExitScene()
{
	Scene* scene = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(scene->getChildByName("GameScene"));
	GameManager* gameManager = GameManager::GetInstance();
	gameManager->SetUILayer(gameScene->GetUILayer());
	gameManager->SetGameLayer(gameScene->GetGameLayer());
	gameManager->SetStage(gameManager->GetStage());

//	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);

	Director::getInstance()->replaceScene(scene);
}

void AdScene::update(float dt)
{
	lifeTime -= dt;

	if (lifeTime < 0)
	{
		ExitScene();
	}
}