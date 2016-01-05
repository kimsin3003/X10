#include "stdafx.h"
#include "EndingScene.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "StageScene.h"
#include "SimpleAudioEngine.h"

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
		return false;
		
	Sequence* seq = Sequence::create(
	DelayTime::create(2.5f),
// 	CallFuncN::create(CC_CALLBACK_0(StageScene::ShowWhiteScene, this)),
// 	DelayTime::create(0.5f),
// 	CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowCrashingScene, this)),
// 	DelayTime::create(9.0f),
// // 	CallFuncN::create(CC_CALLBACK_0(StageScene::ShowWhiteScene, this)),
// // 	DelayTime::create(1.0f),
// 	CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowAfterCrash, this)),
// 	DelayTime::create(5.0f),
// 	CallFuncN::create(CC_CALLBACK_0(StageScene::ShowWhiteScene, this)),
// 	DelayTime::create(2.5f),
	CallFuncN::create(CC_CALLBACK_0(EndingScene::ShowHospital, this)),
nullptr);

	runAction(seq);
	return true;
}

void EndingScene::ShowCrashingScene()
{
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

	removeAllChildrenWithCleanup(true);
	CallFunc* nodding1 = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_0));
	CallFunc* nodding2 = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_1));
	CallFunc* crashingSound = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeSoundEffect, this, FileStuff::SOUND_CRASH));
	CallFunc* crashing1 = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_2));
	CallFunc* crashing2 = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BEFORE_CRASHING_3));
	CallFunc* blackout = CallFunc::create(CC_CALLBACK_0(EndingScene::ChangeBackgroundImg, this, FileStuff::BLACKOUT));

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
		blackout,
		nullptr
		);

	runAction(seq);
}

void EndingScene::ChangeSoundEffect(const char* sound)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(sound, false);
}

void EndingScene::ShowAfterCrash()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();

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

	Sprite* monitor = Sprite::create(FileStuff::MONITOR);
	addChild(monitor);

	monitor->setScale(2.0f);
	monitor->setPosition(Vec2(130, 335));

	m_background->runAction(
		Sequence::create(
		FadeOut::create(5.0f),
		nullptr
		)
	);

	monitor->runAction(
		Sequence::create(
		FadeOut::create(5.0f),
		nullptr)
		);
}

void EndingScene::ShowHospital()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_EAR_RINGING, false, 3.0f);

	removeAllChildrenWithCleanup(true);

	m_background = Sprite::create(FileStuff::HOSPITAL_CLOSED_EYE);
	float scale = (Director::getInstance()->getVisibleSize().width) / (m_background->getContentSize().width);
	m_background->setAnchorPoint(Point::ZERO);
	m_background->setScale(scale);
	addChild(m_background);
	m_background->setOpacity(0);

	m_background->runAction(
		Sequence::create(
		DelayTime::create(5.0f),
		FadeIn::create(5.0f),
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

	monitor->runAction(
		Sequence::create(
		DelayTime::create(2.0f),
		nullptr)
		);

}

void EndingScene::ShowWhiteScene()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(FileStuff::SOUND_EAR_RINGING, false, 3.0f);

	Sprite* white = Sprite::create(FileStuff::WHITE);
	float scale = (Director::getInstance()->getVisibleSize().width) / (white->getContentSize().width);
	white->setAnchorPoint(Point::ZERO);
	white->setScale(scale);
	addChild(white);
}

void EndingScene::RemoveAllChildren(Ref* pSender)
{
	removeAllChildren();
}
