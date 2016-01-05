#include "stdafx.h"
//scene
#include "StageScene.h"
#include "MainScene.h"
#include "GameScene.h"
#include "IntroScene.h"
#include "EndingScene.h"
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
	layer->setName("stageScene");
	layer->setAnchorPoint(Vec2::ZERO);
	layer->setPosition(Vec2::ZERO);

	scene->addChild(layer);

	return scene;
}

bool StageScene::m_justCleared = true;

bool StageScene::init()
{
	if (!LayerColor::initWithColor(Color4B::BLACK))
	{
		return false;
	}

	setName("StageScene");

	m_stageToPlay = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);
	m_maxStageNum = StageInformation::GetMaxStageNum();

	m_background = LoadBackground();
	addChild(m_background);

	m_lightManager = new LightManager();

	SetBGM();

	if (m_stageToPlay == 13)
	{
		scheduleOnce(schedule_selector(StageScene::EndingEvent), 0.0f);
		return true;
	}

	MenuItemImage* backButton = MakeBackButton();
	Menu* menu = Menu::create(backButton, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	SetupLight();
	SetupCharacter();

	return true;
}


void StageScene::ChangeCharacterToButton(Point finalPos, float scale)
{

	MenuItemImage* character = MenuItemImage::create();
	character->setNormalImage(
		Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_CACHE)
		)
	);

	character->setSelectedImage(
		Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_SELECTED)
		)
	);

	character->setScale(scale);
	character->setCallback(CC_CALLBACK_0(StageScene::GotoStage, this, m_stageToPlay));

	Menu* menu = Menu::create(character, nullptr);
	menu->setPosition(finalPos);
	addChild(menu);

}

void StageScene::PlaySound(const char* file)
{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(file);
}

void StageScene::MoveCharacter(Sprite* character, int stageNum)
{
	//애니매이션 및 사운드 재생하는 부분
	Point finishPos = GetCharacterPosition(stageNum);
	Point startPos = GetCharacterPosition(m_stageToPlay - 1);
	Size screenSize = Director::getInstance()->getVisibleSize();
	float startScale = character->getScale()* (1 - startPos.y / (screenSize.height * 1.5));
	float finishScale = character->getScale() * (1 - finishPos.y / (screenSize.height * 1.5));
	float timeLength = 2.0f;
	float standingTime = 2.0f;
	if (stageNum == 1)
	{
		standingTime = 0.1f;
	}

	int last_played_stage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTWALKSTAGE);
	if (last_played_stage != m_stageToPlay)
	{

		//이동
		character->setPosition(startPos);
		character->runAction(Sequence::create(
			DelayTime::create(standingTime), 
			CallFunc::create(CC_CALLBACK_0(StageScene::PlaySound, this, FileStuff::SOUND_FOOTSTEP)),
			MoveTo::create(timeLength, finishPos), 
			CallFunc::create(CC_CALLBACK_0(StageScene::ChangeCharacterToButton, this, finishPos, finishScale)),
			RemoveSelf::create(),
			nullptr
			)
		);

		//크기변화
		character->setScale(startScale);
		ScaleTo* scaleAction = ScaleTo::create(timeLength, finishScale);
		character->runAction(Sequence::create(
			DelayTime::create(standingTime),
			ScaleTo::create(timeLength, finishScale),
			nullptr)
		);

		UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTWALKSTAGE, m_stageToPlay);
	}
	else
	{
		ChangeCharacterToButton(finishPos, finishScale);
	}

}


void StageScene::SetupCharacter()
{

	Sprite* character = Sprite::createWithSpriteFrame(
		SpriteFrameCache::getInstance()->getSpriteFrameByName(FileStuff::CHARACTER_CACHE)
		);

	addChild(character);

	MoveCharacter(character, m_stageToPlay);

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
	
	/*전등 위치에서 얼마나 떨어져 있을지 표시.*/
	float posRatio = .7f ;
	Vec2 currentDelta = Vec2(-50, -70);
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

void StageScene::SetBGM()
{
	if (m_stageToPlay >= 12)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_BEFORE_ENDING_BACKGROUND, true);
	}
	else if (m_stageToPlay >= 5)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_MIDDLE_PHASE_BACKGROUND, true);
	}
	else if (m_stageToPlay >= 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_INITIAL_BACKGROUND, true);
	}
}

void StageScene::SetupLight()
{
	int last_played_stage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTWALKSTAGE);
	if (last_played_stage == 0)
	{
		return;
	}

	if (last_played_stage != m_stageToPlay)
	{
		for (int i = 1; i <= m_maxStageNum && i < last_played_stage; i++)
		{
			addChild(m_lightManager->GetLight(i));
		}
		// 깼을때 나오는 효과
		Sprite* lastLight = m_lightManager->GetLight(last_played_stage);
		lastLight->setOpacity(0);
		FadeIn* fadeIn = FadeIn::create(2.0f);
		lastLight->runAction(fadeIn);
		addChild(lastLight);

		//9탄에 나오는 소녀
		if (m_stageToPlay == 10){
			Sprite* girlLikeGhost = Sprite::create(FileStuff::GHOSTGIRL);
			girlLikeGhost->setOpacity(10);
			girlLikeGhost->setScale(0.3f);
			girlLikeGhost->setPosition(37, 45);
			Sequence* seq = Sequence::create(DelayTime::create(0.5f),
				DelayTime::create(0.5),
				FadeTo::create(0.5f,100),
				DelayTime::create(0.5f),
				FadeOut::create(0.3f),
				DelayTime::create(3.0f),
				FadeTo::create(0.8f, 70),
				FadeOut::create(0.9f),
				nullptr
				);
			girlLikeGhost->runAction(seq);
			lastLight->addChild(girlLikeGhost);
			
		}

	}else
	{
		for (int i = 1; i <= m_maxStageNum && i < m_stageToPlay; i++)
		{
			addChild(m_lightManager->GetLight(i));
		}
	}
}

void StageScene::EndingEvent(float dt)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_BEFORE_ENDING_BACKGROUND);

	Sequence* seq = Sequence::create(
		DelayTime::create(2.3f),
		CallFuncN::create(CC_CALLBACK_0(StageScene::ShowBlinkingLight, this)),
		DelayTime::create(3.0f),
 		CallFuncN::create(CC_CALLBACK_0(StageScene::ShowDeadbody, this)),
 		DelayTime::create(2.0f),
		CallFuncN::create(CC_CALLBACK_0(StageScene::ChangeToEndingScene, this)),
		nullptr);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(FileStuff::SOUND_SHOCKED);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(FileStuff::SOUND_CRASH);

	runAction(seq);
}

void StageScene::ChangeToEndingScene()
{
	Director::getInstance()->replaceScene(EndingScene::createScene());
}

void StageScene::ShowDeadbody()
{
	m_background->removeFromParent();
	m_background = Sprite::create(FileStuff::STAGE_BACKGROUND_13APP);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_SHOCKED, false, 3.0f);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_CRASH, false, 3.0f);
}

void StageScene::SetStreetLight(int isOn)
{
	m_background->removeFromParent();
	if (isOn)
		m_background = Sprite::create(FileStuff::STAGE_BACKGROUND_13ON);
	else
		m_background = Sprite::create(FileStuff::STAGE_BACKGROUND_13OFF);

	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);
}

void StageScene::ShowBlinkingLight()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_STREETLIGHTS);

	CallFunc* lightOff = CallFunc::create(CC_CALLBACK_0(StageScene::SetStreetLight, this, false));
	CallFunc* lightOn = CallFunc::create(CC_CALLBACK_0(StageScene::SetStreetLight, this, true));

	Sequence* seq = Sequence::create(
		lightOn,
		DelayTime::create(0.25f),
		lightOff,
		DelayTime::create(1.0f),
		lightOn,
		DelayTime::create(0.2f),
		lightOff,
		DelayTime::create(0.2f),
		lightOn,
		nullptr);

	runAction(seq);
}

MenuItemImage* StageScene::MakeBackButton()
{
	MenuItemImage* button = MenuItemImage::create(
		FileStuff::PAUSEBUTTON,
		FileStuff::PAUSEBUTTON_CLICKED,
		CC_CALLBACK_1(StageScene::ChangeToMainScene, this));

	Size buttonSize = button->getContentSize();
	float scale = MIN(
		UILayer::PAUSE_BUTTON_WIDTH / buttonSize.width,
		UILayer::PAUSE_BUTTON_HEIGHT / buttonSize.height);
	button->setScale(scale);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	button->setPosition(
		origin.x + visibleSize.width - buttonSize.width *scale / 2,
		origin.y + buttonSize.height * scale / 2
		);

	return button;
}

void StageScene::GotoStage(Ref* pSender, int stageNum)
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

void StageScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void StageScene::ChangeToStageScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageScene::createScene());
}