#include "stdafx.h"
#include "UILayer.h"
#include "MainScene.h"
#include "GameScene.h"
#include "StageScene.h"
#include "GameManager.h"
#include "FileStuff.h"

UILayer* UILayer::createUILayer() ///# �� ��� �Լ��� ���� �ʿ��ϳ�?
{
	UILayer* IU = UILayer::create(); ///# I Seoul U 
	return IU;
}

bool UILayer::init()
{
	if (Layer::init() == false)
		return false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* Pause Button */
	auto pauseButton = MenuItemImage::create(
		FileStuff::PAUSEBUTTON,
		FileStuff::PAUSEBUTTON,
		CC_CALLBACK_1(UILayer::menuButtonCallback, this));
	Size buttonSize = pauseButton->getContentSize();
	float scale = MIN(
		PAUSE_BUTTON_WIDTH / buttonSize.width,
		PAUSE_BUTTON_HEIGHT / buttonSize.height);
	pauseButton->setScale(scale);
	pauseButton->setPosition(Vec2(origin.x + visibleSize.width - (buttonSize*scale).width / 2,
		origin.y + (buttonSize*scale).height / 2));
	
	/*Create Menu*/
	auto menu = Menu::create(pauseButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

//�������� Ŭ���� �� ������ ����.
void UILayer::MakeSuccessWidget(int m_stage)
{

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//���� �޽���
	Label* successMessage = Label::createWithTTF("SUCCESS", "fonts/nanumgothic.ttf", 34); ///# ���� �׸�~
	successMessage->setPosition(visibleSize.width / 2, visibleSize.height / 2 + successMessage->getContentSize().height / 2);


	//�ٽýõ� ��ư
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


	//�������� ����ȭ�� ��ư
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

	/*Create Menu*/
	this->addChild(successMessage);
	auto menu = Menu::create(retryButton, stageSceneButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}


//���н� ������ ����.
void UILayer::MakeFailWidget(int m_stage)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//���� �޽���
	Label* successMessage = Label::createWithTTF("Fail", "fonts/nanumgothic.ttf", 34);
	successMessage->setPosition(visibleSize.width / 2, visibleSize.height / 2 + successMessage->getContentSize().height / 2);


	//�ٽýõ� ��ư
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


	//�������� ����ȭ������ �̵��ϴ� ��ư
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

	/*Create Menu*/
	this->addChild(successMessage);
	auto menu = Menu::create(retryButton, stageSceneButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

}

void UILayer::ChangeToStageScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageScene::createScene());
}

void UILayer::GotoStage(Ref* pSender, int stageNum)
{
	Scene* game = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(game->getChildByName("GameScene"));
	/*stage Information �ҷ����� �κ�.*/
	GameManager::GetInstance()->SetStage(gameScene->GetGameLayer(), stageNum);

	Director::getInstance()->replaceScene(game);
}

void UILayer::menuButtonCallback(Ref* pSender)
{
	ChangeToMainScene(pSender);
}

void UILayer::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}