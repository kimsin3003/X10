#include "stdafx.h"
#include "GameScene.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "Sling.h"
#include "FileStuff.h"

GameScene::GameScene() : m_gameLayer(nullptr), m_uiLayer(nullptr) {}

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
	
	//배경 삽입
	m_background = loadBackground();
	addChild(m_background);

	//캐릭터 삽입
	m_character = loadCharacter();
	m_background->addChild(m_character, 2);

	//레이어 삽입
	m_gameLayer = GameLayer::create();
	m_uiLayer = UILayer::create();
	addChild(m_gameLayer);
	addChild(m_uiLayer);
	
	//게임 매니저 초기화
	m_gameManager = GameManager::GetInstance();

	scheduleUpdate();

	return true;
}

Sprite* GameScene::loadBackground()
{
	Sprite* background = Sprite::create(FileStuff::BACKGROUND);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	background->setOpacity(140);
	return background;
}

Sprite* GameScene::loadCharacter()
{
	Sprite* character = Sprite::create(FileStuff::CHARACTER_HARDPIXEL);
	character->setPosition(40, 12);
	return character;
}

void GameScene::update(float dt)
{
	m_gameManager->Play(m_gameLayer, m_uiLayer);
}