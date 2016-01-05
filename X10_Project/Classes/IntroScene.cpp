#include "stdafx.h"
#include "IntroScene.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "StageScene.h"
#include <AudioEngine.h>
#include <SimpleAudioEngine.h>

Scene* IntroScene::createScene()
{
	Scene* scene = Scene::create();

	Layer* layer = IntroScene::create();
	scene->addChild(layer);

	return scene;
}

bool IntroScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);

	Sprite* background = Sprite::create(FileStuff::BACKGROUND_BOTTOM);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	addChild(background, 0);

	Sprite* character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_CACHE);
	character->setPosition(Point(200, 84));
	addChild(character, 2);

	Sprite* arm = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_ARM);
	arm->setAnchorPoint(Point(0.5, 0.4));
	arm->setPosition(Vec2(8.5f, 45.0f));
	character->addChild(arm, -1);

	Sprite* ufo = Sprite::create(FileStuff::ENEMY);
	ufo->setPosition(Vec2(160, 360));

	int ufo_frameCut = 23;
	float ufo_frameTime = 0.1f;

	Vector<SpriteFrame*> ufo_animFrames;
	ufo_animFrames.reserve(ufo_frameCut);

	for (int i = 0; i < ufo_frameCut; i++)
	{
		string frameNum = to_string(i + 1);
		string aniFileName = FileStuff::ENEMY_DESTRUCT_ANI + frameNum + ".png";
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(aniFileName);
		ufo_animFrames.pushBack(frame);
	}

	Animation* ufo_animation = Animation::createWithSpriteFrames(ufo_animFrames, ufo_frameTime);
	Animate* destructAnimation = Animate::create(ufo_animation);

	Sequence* removeAfterAnimation = Sequence::create(
		DelayTime::create(23 *0.1f),
		RemoveSelf::create(true),
		NULL);

	addChild(ufo, 1);

	Sprite* bullet = Sprite::create();
	float fireScaleRatio = Director::getInstance()->getContentScaleFactor();
	Size fireSize(10 / fireScaleRatio, 10 / fireScaleRatio);

	int bullet_frameCut = 5;
	Vector<SpriteFrame*> bullet_animFrames;
	bullet_animFrames.reserve(bullet_frameCut);
	for (int i = 0; i < bullet_frameCut; i++)
	{
		SpriteFrame* frame = SpriteFrame::create(FileStuff::BULLET, Rect(Point(fireSize.width*i, 0), fireSize));
		bullet_animFrames.pushBack(frame);
	}

	Animation* bullet_animation = Animation::createWithSpriteFrames(bullet_animFrames, 0.1f);
	Animate* bullet_animate = Animate::create(bullet_animation);
	bullet->setPosition(character->getPosition() + Vec2(0.0f, 15.0f));
	bullet->setScale(2.0f);
	bullet->setOpacity(0);
	addChild(bullet);

	float timeLine = 2.0f;

	Sequence* moveArm = Sequence::create(
		DelayTime::create(timeLine),
		RotateBy::create(0.4f, -35),
		DelayTime::create(0.2f),
		RotateBy::create(0.4f, 65),
		DelayTime::create(0.3f),
		RotateBy::create(0.4f, -45),
		nullptr); // total: 3.0 sec

	timeLine += 3.0f;

	Sequence* shootBullet = Sequence::create(
		DelayTime::create(timeLine),
		CallFunc::create(CC_CALLBACK_0(IntroScene::PlaySoundEffect, this, FileStuff::SOUND_FIREWORK_FLYING)),
		FadeIn::create(0.0f),
		MoveTo::create(2.0f, ufo->getPosition() - Vec2(5, 25)),
		DelayTime::create(0.15f),
		RemoveSelf::create(true),
		nullptr); // total: 2.0 sec

	timeLine += 2.15f;

	Sequence* explode = Sequence::create(
		DelayTime::create(timeLine),
		CallFunc::create(CC_CALLBACK_0(IntroScene::PlaySoundEffect, this, FileStuff::SOUND_FIREWORK_EXPLOSION)),
		CallFunc::create(CC_CALLBACK_0(IntroScene::PlayExplosion, this, ufo->getPosition() - Vec2(5, 25))),
		nullptr); // total: 0.5 sec

	timeLine += 0.8f;

	Sequence* destructUFO = Sequence::create(
		DelayTime::create(timeLine),
		CallFunc::create(CC_CALLBACK_0(IntroScene::PlaySoundEffect, this, FileStuff::SOUND_UFO_EXPLODE_DEFAULT)),
		destructAnimation,
		removeAfterAnimation,
		nullptr); // total: 2.5 sec

	timeLine += 4.0f;

	Sequence* changeToStageScene = Sequence::create(
		DelayTime::create(timeLine),
		CallFunc::create(CC_CALLBACK_0(IntroScene::ChangeToStageScene, this)),
		nullptr);

	arm->runAction(moveArm);
	bullet->runAction(RepeatForever::create(bullet_animate));
	bullet->runAction(shootBullet);
	runAction(explode);
	ufo->runAction(destructUFO);
	this->runAction(changeToStageScene);

	return true;
}

void IntroScene::PlaySoundEffect(const char* fileName)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(fileName);
}

void IntroScene::PlayExplosion(const Vec2& pos)
{
	ParticleExplosion* explosion = ParticleExplosion::create();
	explosion->setColor(Color3B());
	explosion->setEmitterMode(kCCParticleModeGravity);
	explosion->setEmissionRate(400);
	explosion->setDuration(4.0f / 15);
	explosion->setLife(1.5f);
	explosion->setEndSize(10);
	explosion->setStartSize(10);
	explosion->setStartSizeVar(0);
	explosion->setEndSizeVar(0);
	explosion->setSpeedVar(0);
	explosion->setSpeed(40 / 3.0f);
	explosion->setPosition(pos);

	addChild(explosion, 3);
}

void IntroScene::ChangeToStageScene()
{
	removeAllChildrenWithCleanup(true);
	Director::getInstance()->replaceScene(StageScene::createScene());
}
