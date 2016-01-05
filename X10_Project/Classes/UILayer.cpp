#include "stdafx.h"
#include "UILayer.h"
#include "MainScene.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "StageScene.h"
#include "GameManager.h"
#include "FileStuff.h"
#include "ConstVars.h"

bool UILayer::init()
{
	if (Layer::init() == false)
	{
		return false;
	}

	Director* dir = Director::getInstance();
	Size visibleSize = dir->getVisibleSize();
	Vec2 origin = dir->getVisibleOrigin();

	MenuItemImage* retryButton = MenuItemImage::create(
		FileStuff::RETRYBUTTON,
		FileStuff::RETRYBUTTON,
		CC_CALLBACK_1(UILayer::GotoStage, this, UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE)));

	Size buttonSize = retryButton->getContentSize();

	float scale = MIN(
		PAUSE_BUTTON_WIDTH / buttonSize.width,
		PAUSE_BUTTON_HEIGHT / buttonSize.height);

	retryButton->setScale(scale);
	retryButton->setPosition(Vec2(origin.x + visibleSize.width - (buttonSize * scale).width / 2 - (buttonSize * scale).width,
		origin.y + (buttonSize * scale).height / 2));

	MenuItemImage* backButton = MenuItemImage::create(
								FileStuff::PAUSEBUTTON,
								FileStuff::PAUSEBUTTON,
								CC_CALLBACK_1(UILayer::ChangeToStageScene, this));
	
	backButton->setScale(scale);
	backButton->setPosition(Vec2(origin.x + visibleSize.width - (buttonSize*scale).width / 2,
							origin.y + (buttonSize*scale).height / 2));
	
	Menu* menu = Menu::create(retryButton, backButton, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	return true;
}

void UILayer::MakeSuccessWidget(int stage)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//성공 이미지
	Sprite* successBoard = Sprite::create(FileStuff::SUCCESS_BOARD);
	successBoard->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
	addChild(successBoard);

	//재시도 버튼
	int current_stage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTWALKSTAGE);
	MenuItemImage* retryButton = MenuItemImage::create(
		FileStuff::RETRYBUTTON,
		FileStuff::RETRYBUTTON,
		CC_CALLBACK_1(UILayer::GotoStage, this, current_stage));

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

	auto menu = Menu::create(retryButton, stageSceneButton, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
}

//실패시 위젯을 띄운다.
void UILayer::MakeFailWidget(int stage)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//실패 이미지
	Sprite* failBoard = Sprite::create(FileStuff::FAIL_BOARD);
	failBoard->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 50);
	addChild(failBoard);

	//재시도 버튼
	int current_stage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTWALKSTAGE);
	MenuItemImage* retryButton = MenuItemImage::create(
		FileStuff::RETRYBUTTON,
		FileStuff::RETRYBUTTON,
		CC_CALLBACK_1(UILayer::GotoStage, this, current_stage));

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

	auto menu = Menu::create(retryButton, stageSceneButton, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
}

void UILayer::AddCurrentBullets(int totalNum, int normalNum, int crossNum)
{

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

	GameManager* gameManager = GameManager::GetInstance();
	gameManager->SetUILayer(gameScene->GetUILayer());
	gameManager->SetGameLayer(gameScene->GetGameLayer());
	gameManager->SetStage(stageNum);

	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);

	Director::getInstance()->replaceScene(sceneWithEffect);
}