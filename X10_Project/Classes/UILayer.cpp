#include "stdafx.h"
#include "UILayer.h"
#include "MainScene.h"
#include "GameScene.h"
#include "StageScene.h"
#include "GameManager.h"
#include "FileStuff.h"

UILayer* UILayer::createUILayer()
{
	UILayer* IU = UILayer::create();
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
		FileStuff::PauseButton,
		FileStuff::PauseButton,
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

//스테이지 클리어 시 위젯을 띄운다.
void UILayer::MakeSuccessWidget(int m_stage)
{

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//성공 메시지
	Label* successMessage = Label::createWithTTF("SUCCESS", "fonts/nanumgothic.ttf", 34);
	successMessage->setPosition(visibleSize.width / 2, visibleSize.height / 2 + successMessage->getContentSize().height / 2);


	//다시시도 버튼
	MenuItemImage* retryButton = MenuItemImage::create(
		FileStuff::PauseButton,
		FileStuff::PauseButton,
		CC_CALLBACK_1(UILayer::GotoStage, this, m_stage));

	Size retryButtonSize = retryButton->getContentSize();

	float retryButtonScale = MIN(
		BUTTON_WIDTH / retryButtonSize.width,
		BUTTON_HEIGHT / retryButtonSize.height);

	retryButton->setScale(retryButtonScale);
	retryButton->setPosition(visibleSize.width / 2 - BUTTON_WIDTH, visibleSize.height / 2 - BUTTON_HEIGHT / 2);


	//스테이지 선택화면 버튼
	MenuItemImage* stageSceneButton = MenuItemImage::create(
		FileStuff::PauseButton,
		FileStuff::PauseButton,
		CC_CALLBACK_1(UILayer::ChangeToStageScene, this));

	Size stageSceneButtonSize = stageSceneButton->getContentSize();

	float stageSceneButtonScale = MIN(
		BUTTON_WIDTH / stageSceneButtonSize.width,
		BUTTON_HEIGHT / stageSceneButtonSize.height);

	stageSceneButton->setScale(stageSceneButtonScale);
	stageSceneButton->setPosition(visibleSize.width / 2, visibleSize.height / 2 - BUTTON_HEIGHT / 2);


	//다음 스테이지로 가는 버튼
	MenuItemImage* nextStageButton = MenuItemImage::create(
		FileStuff::PauseButton,
		FileStuff::PauseButton,
		CC_CALLBACK_1(UILayer::GotoStage, this, m_stage + 1));

	Size nextStageButtonSize = nextStageButton->getContentSize();

	float nextStageButtonScale = MIN(
		BUTTON_WIDTH / nextStageButtonSize.width,
		BUTTON_HEIGHT / nextStageButtonSize.height);

	nextStageButton->setScale(nextStageButtonScale);
	nextStageButton->setPosition(visibleSize.width / 2 + BUTTON_WIDTH, visibleSize.height / 2 - BUTTON_HEIGHT / 2);


	/*Create Menu*/
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

	//성공 메시지
	Label* successMessage = Label::createWithTTF("Fail", "fonts/nanumgothic.ttf", 34);
	successMessage->setPosition(visibleSize.width / 2, visibleSize.height / 2 + successMessage->getContentSize().height / 2);


	//다시시도 버튼
	MenuItemImage* retryButton = MenuItemImage::create(
		FileStuff::PauseButton,
		FileStuff::PauseButton,
		CC_CALLBACK_1(UILayer::GotoStage, this, m_stage));

	Size retryButtonSize = retryButton->getContentSize();

	float retryButtonScale = MIN(
		BUTTON_WIDTH / retryButtonSize.width,
		BUTTON_HEIGHT / retryButtonSize.height);

	retryButton->setScale(retryButtonScale);
	retryButton->setPosition(visibleSize.width / 2 - BUTTON_WIDTH, visibleSize.height / 2 - BUTTON_HEIGHT / 2);


	//스테이지 선택화면으로 이동하는 버튼
	MenuItemImage* stageSceneButton = MenuItemImage::create(
		FileStuff::PauseButton,
		FileStuff::PauseButton,
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
	/*stage Information 불러오는 부분.*/
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

