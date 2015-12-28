#include "stdafx.h"
#include "GameScene.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "Sling.h"
#include "FileStuff.h"

Scene* GameScene::createScene()
{
	Scene* scene = Scene::create();

	Layer* layer = GameScene::create();
	layer->setName("GameScene");
	scene->addChild(layer);
	
	return scene;
}

bool GameScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}
	
	m_background = LoadBackground();
	addChild(m_background);

	Sprite* bgBottom = LoadBGBottom();
	addChild(bgBottom, 2);

	m_gameLayer = GameLayer::create();
	addChild(m_gameLayer);
	
	m_uiLayer = UILayer::create();
	addChild(m_uiLayer, 10);
	
	m_gameManager = GameManager::GetInstance();

	scheduleUpdate();

	return true;
}

Sprite* GameScene::LoadBackground()
{
	Sprite* background = Sprite::create(FileStuff::BACKGROUND_BASE);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	background->setOpacity(140);
	return background;
}

Sprite* GameScene::LoadBGBottom()
{
	Sprite * bottom = Sprite::create(FileStuff::BACKGROUND_BOTTOM);
	float scale = (Director::getInstance()->getVisibleSize().width) / (bottom->getContentSize().width);
	bottom->setAnchorPoint(Point::ZERO);
	bottom->setScale(scale);
	return bottom;
}

void GameScene::update(float dt)
{
	m_gameManager->Play(m_gameLayer, m_uiLayer);
}