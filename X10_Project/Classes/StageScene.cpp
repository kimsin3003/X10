#include "stdafx.h"
//scene
#include "StageScene.h"
#include "MainScene.h"
#include "GameScene.h"
//layer
#include "UILayer.h"
//info
#include "LightManager.h"
#include "StageInformation.h"
//manager
#include "GameManager.h"
//config
#include "ConstVars.h"
#include "FileStuff.h"
//etc
#include "Sling.h"
#include <SimpleAudioEngine.h>

Scene* StageScene::createScene()
{
	Scene* scene = Scene::create();
	scene->setAnchorPoint(Vec2::ZERO);
	scene->setPosition(Vec2::ZERO);

	Layer* layer = StageScene::create();
	layer->setAnchorPoint(Vec2::ZERO);
	layer->setPosition(Vec2::ZERO);

	scene->addChild(layer);

	return scene;
}

bool StageScene::m_hasCharacterMoved = false;

bool StageScene::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	setName("StageScene");

	m_stageToPlay = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);
	m_maxStageNum = StageInformation::GetMaxStageNum();

	if (m_stageToPlay == 0)
	{
		scheduleOnce(schedule_selector(StageScene::IntroEvent), 0.0f);
		return true;
	}


	m_background = LoadBackground();
	addChild(m_background);

	m_lightManager = new LightManager();


	if (m_stageToPlay == 13)
	{
		scheduleOnce(schedule_selector(StageScene::EndingEvent), 0.0f);
		return true;
	}

	SetupLight();

	SetupCharacter();

	return true;
}

void StageScene::SetupCharacter()
{
	Vector<MenuItem*> menuList;

	MenuItemImage* backButton = MakeBackButton();
	menuList.pushBack(backButton);
	
	MenuItemImage* menuItem = MenuItemImage::create();
	menuItem->setNormalImage(
		Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_STANDING)
		)
	);
	menuItem->setSelectedImage(
		Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_SELECTED)
		)
	);

	menuItem->setCallback(CC_CALLBACK_0(StageScene::GotoStage, this, m_stageToPlay));
	
	menuItem = MoveCharacter(menuItem, m_stageToPlay);

	menuList.pushBack(menuItem);
	Menu* menu = Menu::createWithArray(menuList);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);
}

Point StageScene::GetCharacterPosition(int stage)
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (stage == 0)
	{
		return Point(screenSize.width / 2 , 0);
	}
	LightManager mng;
	int odd = stage % 2;
	Vec2 lightPos = mng.GetPosition(stage);
	float posRatio = 1.f;
	
	/*
	lightPos와 그 이전과의 lightPos , 가운데 중앙선 이 이루는 사다리 꼴에서
	posRatio비율만큼의 대각선 거리. 짝수 탄에는 거기서 y축으로 절반만큼 간 거리.
	*/

	Vec2 currentDelta = Vec2(-50, -50);
	currentDelta.x *= -(odd);
	currentDelta.x -= 20;

	return lightPos + posRatio * currentDelta;
}

Sprite* StageScene::LoadBackground()
{
	Sprite* background; 
	switch (m_stageToPlay)
	{
	case 1:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_01);
		break;
	case 2:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_02);
		break;
	case 3:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_03);
		break;
	case 4:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_04);
		break;
	case 5:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_05);
		break;
	case 6:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_06);
		break;
	case 7:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_07);
		break;
	case 8:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_08);
		break;
	case 9:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_09);
		break;
	case 10:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_10);
		break;
	case 11:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_11);
		break;
	case 12:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_12);
		break;
	case 13:
		background = Sprite::create(FileStuff::STAGE_BACKGROUND_13OFF);
		break;
	}

	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);

	return background;
}

void StageScene::SetupLight()
{
	switch (m_stageToPlay)
	{
	case 14:
	case 13:
		addChild(m_lightManager->GetLight(12));
	case 12:
		if (m_stageToPlay <= 14)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_BEFORE_ENDING_BACKGROUND, true);
		}
		addChild(m_lightManager->GetLight(11));
	case 11:
		addChild(m_lightManager->GetLight(10));
	case 10:
		addChild(m_lightManager->GetLight(9));
	case 9:
		addChild(m_lightManager->GetLight(8));
	case 8:
		addChild(m_lightManager->GetLight(7));
	case 7:
		addChild(m_lightManager->GetLight(6));
	case 6:
		addChild(m_lightManager->GetLight(5));
	case 5:
		if (m_stageToPlay <= 5)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_MIDDLE_PHASE_BACKGROUND, true);
		}
		addChild(m_lightManager->GetLight(4));
	case 4:
		addChild(m_lightManager->GetLight(3));
	case 3:
		addChild(m_lightManager->GetLight(2));
	case 2:
		addChild(m_lightManager->GetLight(1));
	default:
		break;
	}
}

Sprite* StageScene::LoadCharacter()
{
	Sprite* character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_STANDING);
	character->setPosition(Sling::create()->SLING_POSITION - Point(0, 15));

	return character;
}

MenuItemImage* StageScene::MoveCharacter(MenuItemImage* character, int stageNum)
{
	//MenuItemImage* character = dynamic_cast<MenuItemImage*>(pSender);
	//애니매이션 및 사운드 재생하는 부분
	Point finishPos = GetCharacterPosition(stageNum);
	Point startPos = GetCharacterPosition(m_stageToPlay - 1);
	Size screenSize = Director::getInstance()->getVisibleSize();
	float startScale = character->getScale()* (1 - startPos.y / (screenSize.height * 2.0));
	float finishScale = character->getScale() * (1 - finishPos.y / (screenSize.height * 2.0));
	float timeLength = 2.0f;

	if (!m_hasCharacterMoved)
	{

		//소리
		int stepsound = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_FOOTSTEP);

		//이동
		character->setPosition(startPos);
		DelayTime* delay = DelayTime::create(0.1);
		MoveTo* move = MoveTo::create(timeLength, finishPos);
		Sequence* action = Sequence::create(delay, move, NULL);
		character->runAction(action);

		//크기변화
		character->setScale(startScale);
		ScaleTo* scaleAction = ScaleTo::create(timeLength, finishScale);
		character->runAction(scaleAction);

		m_hasCharacterMoved = true;
	}
	else
	{
		character->setPosition(finishPos);
		character->setScale(startScale);
	}

	return character;
}

void StageScene::GotoStage(Ref* pSender, int stageNum)
{
	Scene* scene = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(scene->getChildByName("GameScene"));

	GameManager::GetInstance()->SetStage(gameScene->GetGameLayer(), gameScene->GetUILayer(), stageNum);
	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);

	Director::getInstance()->replaceScene(sceneWithEffect);
}

void StageScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void StageScene::ChangeToStageScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageScene::createScene());
}

void StageScene::IntroEvent(float dt)
{
	//FadeIn Version	
	Vec2 deltaPos = Vec2(0, 16.5f);
	Vec2 textPos = Vec2(0.0f, 480.0f);

	PrintIntroText("Why am I standing on a highway?", textPos, 2.0f, 1.0f);
	PrintIntroText("Hmm.. and what are these in my pockets?", textPos-=deltaPos, 6.5f, 1.0f);
	PrintIntroText("Oh my, what are those above the sky?", textPos -= deltaPos*6, 10.5f, 1.25f);
	PrintIntroText("Wait, here's a note", textPos -= deltaPos * 2, 14.0f, 1.0f);
	PrintIntroText("\"Kill them, then I'll let you go\"", textPos -= deltaPos * 4, 18.0f, 1.60f);
	PrintIntroText("Who is doing this fuck to me...?", textPos -= deltaPos * 2, 23.0f, 1.0f);
	PrintIntroText("I'll find you and I'll kill you", textPos -= deltaPos * 2, 27.0f, 1.0f);

	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);

	CallFuncN* callFuncN = CallFuncN::create(
		CC_CALLBACK_1(StageScene::ChangeToStageScene, this));

	Sequence* seq = Sequence::create(
		DelayTime::create(30.0f),
		callFuncN,
		nullptr);

	runAction(seq);
}

void StageScene::PrintIntroText(const string& message, const Vec2& pos, float startTime, float textScale)
{
	Label* text = Label::create(
		message, FileStuff::FONT_ARIAL, 14.5f);

	text->setAlignment(TextHAlignment::LEFT);
	text->setScale(1.00f * textScale);
	text->setOpacity(0);
	text->setAnchorPoint(Vec2(0, 1));
	text->setPosition(pos);
	addChild(text);

	Sequence* seq = Sequence::create(
		DelayTime::create(startTime),
		FadeIn::create(0),
		NULL);

	text->runAction(seq);
}

void StageScene::EndingEvent(float dt)
{
	Sequence* seq = Sequence::create(
		DelayTime::create(2.5f),
		CallFuncN::create(CC_CALLBACK_0(StageScene::ShowBlinkingGaro, this)),
		DelayTime::create(4.0f),
		CallFuncN::create(CC_CALLBACK_0(StageScene::ShowDeadbody, this)),
		DelayTime::create(2.0f),
		CallFuncN::create(CC_CALLBACK_0(StageScene::ShowWhiteScene, this)),
		DelayTime::create(3.0f),
		CallFuncN::create(CC_CALLBACK_0(StageScene::ShowCrashingScene, this)), //효과음 바로 - 끼이이이익 -> 쾅!!!
		nullptr);

	runAction(seq);
}

void StageScene::ShowWhiteScene()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_EAR_RINGING, false, 3.0f);

	Sprite* white = Sprite::create(FileStuff::WHITE);
	float scale = (Director::getInstance()->getVisibleSize().width) / (white->getContentSize().width);
	white->setAnchorPoint(Point::ZERO);
	white->setScale(scale);	
	addChild(white);
}

void StageScene::ShowDeadbody()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_SHOCKED, false, 3.0f);

	m_background->removeFromParent();
	m_background = Sprite::create(FileStuff::STAGE_BACKGROUND_13APP);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);
}

void StageScene::GaroOn()
{
	m_background->removeFromParent();
	m_background = Sprite::create(FileStuff::STAGE_BACKGROUND_13ON);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);
}

void StageScene::GaroOff()
{
	m_background->removeFromParent();
	m_background = Sprite::create(FileStuff::STAGE_BACKGROUND_13OFF);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);
}

void StageScene::ShowBlinkingGaro()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_STREETLIGHTS);

	CallFunc* garoOff = CallFunc::create(CC_CALLBACK_0(StageScene::GaroOff, this));
	CallFunc* garoOn = CallFunc::create(CC_CALLBACK_0(StageScene::GaroOn, this));

	Sequence* seq = Sequence::create(
		garoOn,
		DelayTime::create(0.25f),
		garoOff,
		DelayTime::create(1.0f),
		garoOn,
		DelayTime::create(0.2f),
		garoOff,
		DelayTime::create(0.2f),
		garoOn,
		nullptr);

	runAction(seq);
}

void StageScene::ChangeBackgroundImg(string bgImg)
{
	Vector<Node*> childs = getChildren();

	for (int i = 0; i < childs.size(); i++)
	{
		childs.at(i)->removeFromParent();
	}

	Sprite* backgroundImg = Sprite::create(bgImg);

	float scale = (Director::getInstance()->getVisibleSize().width) / (backgroundImg->getContentSize().width);
	backgroundImg->setAnchorPoint(Point::ZERO);
	backgroundImg->setScale(scale);
	backgroundImg->setOpacity(140);
	addChild(backgroundImg);
}

void StageScene::ChangeSoundEffect(const char* sound)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sound, false);
}

void StageScene::ShowCrashingScene()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	Vector<Node*> childs = getChildren();

	for (int i = 0; i < childs.size(); i++)
	{
		childs.at(i)->removeFromParent();
	}

	CallFunc* crashing0 = CallFunc::create(CC_CALLBACK_0(StageScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_0));
	CallFunc* crashingSound = CallFunc::create(CC_CALLBACK_0(StageScene::ChangeSoundEffect, this, FileStuff::SOUND_CRASH));
	CallFunc* crashing1 = CallFunc::create(CC_CALLBACK_0(StageScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_1));
	CallFunc* crashing2 = CallFunc::create(CC_CALLBACK_0(StageScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_2));
	CallFunc* blackout = CallFunc::create(CC_CALLBACK_0(StageScene::ChangeBackgroundImg, this, FileStuff::BLACKOUT));



	Sequence* seq = Sequence::create(
		crashing0,
		crashingSound,
		DelayTime::create(1.7f),
		crashing1,
		DelayTime::create(0.2f),
		crashing2,
		DelayTime::create(1.2f),
		blackout,
		nullptr
	);

	runAction(seq);

}

MenuItemImage* StageScene::MakeBackButton()
{
	MenuItemImage* button = MenuItemImage::create(
		FileStuff::PAUSEBUTTON,
		FileStuff::PAUSEBUTTON,
		CC_CALLBACK_1(StageScene::ChangeToMainScene, this));

	Size buttonSize = button->getContentSize();
	float scale = MIN(
		UILayer::PAUSE_BUTTON_WIDTH / buttonSize.width,
		UILayer::PAUSE_BUTTON_HEIGHT / buttonSize.height);
	button->setScale(scale);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	button->setPosition(
		origin.x + visibleSize.width - buttonSize.width*scale / 2,
		origin.y + buttonSize.height*scale / 2
		);

	return button;
}