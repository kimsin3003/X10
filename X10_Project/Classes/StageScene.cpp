#include "stdafx.h"
//scene
#include "StageScene.h"
#include "MainScene.h"
#include "GameScene.h"
#include "TutorialScene.h"
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

	m_stageToPlay = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);
	m_maxStageNum = StageInformation::GetMaxStageNum();

	if (m_stageToPlay < 1 || m_stageToPlay > m_maxStageNum)
	{
		UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);
		UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTWALKSTAGE, 0);
		m_stageToPlay = 1;
	}

	if (m_stageToPlay == m_maxStageNum)
	{
		scheduleOnce(schedule_selector(StageScene::ChangeToEndingScene), 1.00f);

		return true;
	}

	m_background = LoadBackground();
	addChild(m_background);

	m_lightManager = new LightManager();

	//don't modify order of setting
	SetBGM();
	SetLight();
	SetWaitSign();
	SetCharacter();

	MenuItemImage* backButton = MakeBackButton();
	Menu* menu = Menu::create(backButton, nullptr);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	return true;
}

void StageScene::SetWaitSign()
{
	Sprite* wait = Sprite::create(FileStuff::WAIT);
	wait->setPosition(Vec2(270, 460));
	wait->setName("waitSign");
	addChild(wait);

	FadeOut* fadeOut = FadeOut::create(1.0f);
	FadeIn* fadeIn = FadeIn::create(1.0f);
	Sequence* _blink = Sequence::createWithTwoActions(fadeOut, fadeIn);
	RepeatForever* blink = RepeatForever::create(_blink);
	wait->runAction(blink);
}

void StageScene::ChangeCharacterToButton(Sprite* characterSprite, Point finalPos, float scale)
{
	characterSprite->removeFromParent();

	getChildByName("waitSign")->removeFromParent();
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
	//�ִϸ��̼� �� ���� ����ϴ� �κ�
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

		//�̵�
		character->setPosition(startPos);
		character->runAction(Sequence::create(
			DelayTime::create(standingTime), 
			CallFunc::create(CC_CALLBACK_0(StageScene::PlaySound, this, FileStuff::SOUND_FOOTSTEP)),
			MoveTo::create(timeLength, finishPos), 
			CallFunc::create(CC_CALLBACK_0(StageScene::ChangeCharacterToButton, this, character, finishPos, finishScale)),
			RemoveSelf::create(),
			nullptr
			)
		);

		//ũ�⺯ȭ
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
		ChangeCharacterToButton(character, finishPos, finishScale);
	}
}


void StageScene::SetCharacter()
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
	
	/*���� ��ġ���� �󸶳� ������ ������ ǥ��.*/
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
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_BEFORE_ENDING_BACKGROUND, true);
	}
	else if (m_stageToPlay >= 5)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_MID_PHASE_BACKGROUND, true);
	}
	else if (m_stageToPlay >= 1)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_INITIAL_BACKGROUND, true);
	}
}

void StageScene::SetLight()
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
		// ������ ������ ȿ��
		Sprite* lastLight = m_lightManager->GetLight(last_played_stage);
		lastLight->setOpacity(0);
		FadeIn* fadeIn = FadeIn::create(2.0f);
		lastLight->runAction(fadeIn);
		addChild(lastLight);

		//9ź�� ������ �ҳ�
		if (m_stageToPlay == 10){
			Sprite* girlLikeGhost = Sprite::create(FileStuff::GHOSTGIRL);
			girlLikeGhost->setOpacity(10);
			girlLikeGhost->setScale(0.4f);
			girlLikeGhost->setPosition(37, 45);
			Sequence* seq = Sequence::create(
				DelayTime::create(1.5f),
				FadeTo::create(0.3f, 100),
				DelayTime::create(0.5f),
				FadeOut::create(0.4f),
				DelayTime::create(1.0f),
				FadeTo::create(0.0f, 200),
				DelayTime::create(0.15f),
				FadeOut::create(0.0f),
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

void StageScene::ChangeToEndingScene(float dt)
{
	Director::getInstance()->replaceScene(EndingScene::createScene());
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
	//////////////////////////������ �κ�////////////////////////////////////
	if (stageNum == 1)
	{
		Scene* tutorialScene = TutorialScene::createScene();
		TutorialScene::cameFromStageScene = true;
		Director::getInstance()->replaceScene(tutorialScene);
		return;
	}

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