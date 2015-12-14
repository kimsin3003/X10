#include "stdafx.h"
#include "UILayer.h"
#include "MainScene.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "StageScene.h"
#include "GameManager.h"
#include "FileStuff.h"

bool UILayer::init()
{
	if (Layer::init() == false)
	{
		return false;
	}


	Director* dir = Director::getInstance();
	Size visibleSize = dir->getVisibleSize();
	Vec2 origin = dir->getVisibleOrigin();

	MenuItemImage* backButton = MenuItemImage::create(
								FileStuff::PAUSEBUTTON,
								FileStuff::PAUSEBUTTON,
								CC_CALLBACK_1(UILayer::ChangeToStageScene, this));
	
	Size buttonSize = backButton->getContentSize();
	float scale = MIN(
		PAUSE_BUTTON_WIDTH / buttonSize.width,
		PAUSE_BUTTON_HEIGHT / buttonSize.height);
	
	backButton->setScale(scale);
	backButton->setPosition(Vec2(origin.x + visibleSize.width - (buttonSize*scale).width / 2,
							origin.y + (buttonSize*scale).height / 2));
	
	Menu* menu = Menu::create(backButton, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	return true;
}

void UILayer::MakeSuccessWidget(int m_stage)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//성공 메시지
	Label* successMessage = Label::createWithTTF("SUCCESS", "fonts/nanumgothic.ttf", 34);
	successMessage->setPosition(visibleSize.width / 2, visibleSize.height / 2 + successMessage->getContentSize().height / 2);

	//재시도 버튼
	MenuItemImage* retryButton = MenuItemImage::create(
		FileStuff::RETRYBUTTON,
		FileStuff::RETRYBUTTON,
		CC_CALLBACK_1(UILayer::GotoStage, this, m_stage));

	Size retryButtonSize = retryButton->getContentSize();

	float retryButtonScale = MIN(
		BUTTON_WIDTH / retryButtonSize.width,
		BUTTON_HEIGHT / retryButtonSize.height);

	retryButton->setScale(retryButtonScale);
	retryButton->setPosition(visibleSize.width / 2 - BUTTON_WIDTH, visibleSize.height / 2 - BUTTON_HEIGHT / 2);

	//다음 버튼
	MenuItemImage* stageSceneButton = MenuItemImage::create(
		FileStuff::NEXTBUTTON,
		FileStuff::NEXTBUTTON,
		CC_CALLBACK_1(UILayer::ChangeToStageScene, this));

	Size stageSceneButtonSize = stageSceneButton->getContentSize();

	float stageSceneButtonScale = MIN(
		BUTTON_WIDTH / stageSceneButtonSize.width,
		BUTTON_HEIGHT / stageSceneButtonSize.height);

	stageSceneButton->setScale(stageSceneButtonScale);
	stageSceneButton->setPosition(visibleSize.width / 2 + BUTTON_WIDTH, visibleSize.height / 2 - BUTTON_HEIGHT / 2);

	this->addChild(successMessage);
	auto menu = Menu::create(retryButton, stageSceneButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

//실패시 위젯을 띄운다.
void UILayer::MakeFailWidget(int m_stage)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//실패 메시지
	Label* successMessage = Label::createWithTTF("Fail", "fonts/nanumgothic.ttf", 34);
	successMessage->setPosition(visibleSize.width / 2, visibleSize.height / 2 + successMessage->getContentSize().height / 2);

	//재시도 버튼
	MenuItemImage* retryButton = MenuItemImage::create(
		FileStuff::RETRYBUTTON,
		FileStuff::RETRYBUTTON,
		CC_CALLBACK_1(UILayer::GotoStage, this, m_stage));

	Size retryButtonSize = retryButton->getContentSize();

	float retryButtonScale = MIN(
		BUTTON_WIDTH / retryButtonSize.width,
		BUTTON_HEIGHT / retryButtonSize.height);

	retryButton->setScale(retryButtonScale);
	retryButton->setPosition(visibleSize.width / 2 - BUTTON_WIDTH, visibleSize.height / 2 - BUTTON_HEIGHT / 2);


	//스테이지 선택화면 버튼
	MenuItemImage* stageSceneButton = MenuItemImage::create(
		FileStuff::BACKBUTTON,
		FileStuff::BACKBUTTON,
		CC_CALLBACK_1(UILayer::ChangeToStageScene, this));

	Size stageSceneButtonSize = stageSceneButton->getContentSize();

	float stageSceneButtonScale = MIN(
		BUTTON_WIDTH / stageSceneButtonSize.width,
		BUTTON_HEIGHT / stageSceneButtonSize.height);

	stageSceneButton->setScale(stageSceneButtonScale);
	stageSceneButton->setPosition(visibleSize.width / 2 + BUTTON_WIDTH, visibleSize.height / 2 - BUTTON_HEIGHT / 2);

	this->addChild(successMessage);
	auto menu = Menu::create(retryButton, stageSceneButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void UILayer::ChangeToStageScene(Ref* pSender)
{
	TransitionProgressOutIn* sceneWithEffect = TransitionProgressOutIn::create(0.75f, StageScene::createScene());
	Director::getInstance()->replaceScene(sceneWithEffect);
}

void UILayer::GotoStage(Ref* pSender, int stageNum)
{
	Scene* scene = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(scene->getChildByName("GameScene"));

	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);
	
	GameManager::GetInstance()->SetStage(gameScene->GetGameLayer(), stageNum);
	Director::getInstance()->replaceScene(sceneWithEffect);
}