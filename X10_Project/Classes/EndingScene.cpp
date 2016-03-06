#include "stdafx.h"
#include "EndingScene.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "StageScene.h"
#include "SimpleAudioEngine.h"
#include "CreditScene.h"

Scene* EndingScene::createScene()
{
	Scene* scene = Scene::create();

	Layer* layer = EndingScene::create();
	scene->addChild(layer);

	return scene;
}

bool EndingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FileStuff::SOUND_BEFORE_ENDING_BACKGROUND);

	m_background = Sprite::create(FileStuff::STAGE_BACKGROUND_13OFF);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setScale(scale);
	m_background->setAnchorPoint(Vec2::ZERO);
	addChild(m_background);

	Sequence* seq = Sequence::create(
		DelayTime::create(2.3f),

		CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowBlinkingLight, this)),
		DelayTime::create(3.0f),

		CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowDeadbody, this)),
		DelayTime::create(3.3f),

		CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowCrashingScene, this)),
		DelayTime::create(9.0f),

		CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowAfterCrash, this)),
		DelayTime::create(7.0f),

		CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowWhiteScene, this)),
		DelayTime::create(3.0f),

		CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowHospital, this)),
		DelayTime::create(29.0f),

		CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeToCreditScene, this)),
		nullptr);

	runAction(seq);

	return true;
}

void EndingScene::ShowCrashingScene()
{
	removeAllChildrenWithCleanup(true);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FileStuff::SOUND_ENDING_BACKGROUND);

	CallFunc* nodding1 = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_0));
	CallFunc* nodding2 = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_1));
	CallFunc* crashingSound = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeSoundEffect, this, FileStuff::SOUND_CRASH));
	CallFunc* crashing1 = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_2));
	CallFunc* crashing2 = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_3));

	Sequence* seq = Sequence::create(
		crashingSound,
		nodding1,
		DelayTime::create(2.0f),
		nodding2,
		DelayTime::create(1.0f),
		nodding1,
		DelayTime::create(2.0f),
		nodding2,
		DelayTime::create(1.5f),
		crashing1,
		DelayTime::create(0.2f),
		crashing2,
		DelayTime::create(1.2f),
		nullptr
		);

	runAction(seq);
}
void EndingScene::ShowDeadbody()
{
	m_background->removeFromParent();
	m_background = Sprite::create(FileStuff::STAGE_BACKGROUND_13APP);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_SHOCKED, false);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_CRASH, false);
}

void EndingScene::ShowBlinkingLight()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_STREETLIGHTS);

	CallFunc* lightOff = CallFunc::create(CC_CALLBACK_0(EndingScene::SetStreetLight, this, false));
	CallFunc* lightOn = CallFunc::create(CC_CALLBACK_0(EndingScene::SetStreetLight, this, true));

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

void EndingScene::ChangeSoundEffect(const char* sound)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sound);
}

void EndingScene::SetStreetLight(int isOn)
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


void EndingScene::ShowAfterCrash()
{
	m_background = Sprite::create(FileStuff::AFTER_CRASHED);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);
}

void EndingScene::ChangeBackgroundImg(string bgImg)
{
	removeAllChildren();
	m_background = Sprite::create(bgImg);

	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	m_background->setName("background");
	addChild(m_background);
}

void EndingScene::AddMonitor()
{
	Sprite* monitor = Sprite::create(FileStuff::MONITOR);

	monitor->setPosition(Vec2(130, 335));
	monitor->setScale(2.0f);

	monitor->setName("monitor");
	addChild(monitor);
}

void EndingScene::FadeOut()
{
	removeAllChildren();

	m_background = Sprite::create(FileStuff::HOSPITAL_WAKED);

	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);

	m_background->runAction(
		Sequence::create(
		FadeOut::create(5.0f),
		nullptr
		)
		);

	Sprite* monitor = Sprite::create(FileStuff::MONITOR);

	monitor->setScale(2.0f);
	monitor->setPosition(Vec2(130, 335));
	addChild(monitor);

	monitor->runAction(
		Sequence::create(
		FadeOut::create(5.0f),
		nullptr)
		);

	Sprite* ufo = Sprite::create(FileStuff::HOSPITAL_UFO);
	ufo->setScale(1.7f);
	ufo->setPosition(Vec2(230, 239));
	ufo->runAction(Sequence::create(
		DelayTime::create(3.0f),
		RotateBy::create(5.0f, -90.0f),
		FadeOut::create(3.0f),
		nullptr
		)
	);
	addChild(ufo);
	
}

void EndingScene::ShowHospital()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_EAR_RINGING);

	m_background = Sprite::create(FileStuff::HOSPITAL_CLOSED_EYE);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);
	m_background->setOpacity(0);

	m_background->runAction(
		Sequence::create(
		FadeIn::create(12.0f),
		nullptr)
		);

	Sequence* standing = Sequence::create(
 		DelayTime::create(12.0f),
 		CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::HOSPITAL_OPEN_EYE)),
 		CallFunc::create(CC_CALLBACK_0(EndingScene::AddMonitor, this)),
 		DelayTime::create(1.0f),
 		CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::HOSPITAL_WAKING)),
 		CallFunc::create(CC_CALLBACK_0(EndingScene::AddMonitor, this)),
 		DelayTime::create(0.5f),
 		CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::HOSPITAL_WAKED)),
 		CallFunc::create(CC_CALLBACK_0(EndingScene::AddMonitor, this)),
 		DelayTime::create(3.0f),
		CallFunc::create(CC_CALLBACK_0(EndingScene::FadeOut, this)),
		nullptr
		);

	runAction(standing);

	Sprite* monitor = Sprite::create(FileStuff::MONITOR);
	addChild(monitor);

	monitor->setScale(2.0f);
	monitor->setPosition(Vec2(130, 335));
	monitor->setOpacity(0);

	monitor->runAction(
		FadeIn::create(2.0f)
		);
}

void EndingScene::ShowWhiteScene()
{
	removeAllChildrenWithCleanup(true);
	Sprite* white = Sprite::create(FileStuff::WHITE);
	float scale = (Director::getInstance()->getVisibleSize().width) / (white->getContentSize().width);
	white->setAnchorPoint(Point::ZERO);
	white->setScale(scale);
	white->runAction(FadeOut::create(1.5f));
	addChild(white);
}

void EndingScene::RemoveAllChildren()
{
	removeAllChildren();
}

void EndingScene::ChangeToCreditScene()
{
	UserDefault::getInstance()->setBoolForKey(ConstVars::CLEARED_ONCE, true);
	Director::getInstance()->replaceScene(CreditScene::createScene());
}
