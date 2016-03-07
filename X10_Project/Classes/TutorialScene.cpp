#include "stdafx.h"
#include "TutorialScene.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "GameScene.h"
#include "GameManager.h"
#include <AudioEngine.h>
#include <SimpleAudioEngine.h>

bool TutorialScene::cameFromStageScene = false;

Scene* TutorialScene::createScene()
{
	Scene* scene = Scene::create();

	Layer* layer = TutorialScene::create();
	scene->addChild(layer);

	return scene;
}

bool TutorialScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	cameFromStageScene = false;

	MenuItemImage* skipButton = MenuItemImage::create(FileStuff::SKIP_BUTTON, FileStuff::SKIP_BUTTON, CC_CALLBACK_0(TutorialScene::ChangeToProperScene, this));
	skipButton->setPosition(Vec2(40, 90));
	skipButton->setScale(0.5f); 
	skipButton->setOpacity(0.0f);

	FadeOut* fadeOut = FadeOut::create(1.0f);
	FadeIn* fadeIn = FadeIn::create(1.0f);
	Sequence* _blink = Sequence::create(DelayTime::create(3.0f), fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, NULL);
	
	//RepeatForever* blink = RepeatForever::create(_blink);

	//Sequence* allAction = Sequence::create(DelayTime::create(3.0f), blink, NULL);

	skipButton->runAction(_blink);

	Menu* menu = Menu::createWithItem(skipButton);
	menu->setPosition(Vec2::ZERO);
	menu->setName("Buttons");
	addChild(menu, 1);

	/////////////////////////// sprites ///////////////////////////
	Sprite* background = Sprite::create(FileStuff::BACKGROUND_BOTTOM);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	addChild(background, 0);

	Sprite* character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_CACHE);
	character->setPosition(Point(200, 84));
	addChild(character, 2);

	Sprite* range = Sprite::create(FileStuff::SLING_RANGE);
	range->setAnchorPoint(Vec2(0.5f, 0.0f));
	range->setPosition(Vec2(10.0f, 40.0f));
	character->addChild(range, -2);

	Sprite* line = Sprite::create(FileStuff::SLING_LINE);
	line->setAnchorPoint(Vec2(0.5f, 0.0f));
	line->setPosition(Vec2(29.5f, 40.0f));
	line->setOpacity(60);
	character->addChild(line, -2);

	Sprite* dot = Sprite::create(FileStuff::SLING_LINE_DOT);
	dot->setPosition(Vec2(29.5f, 120.0f));
	dot->setScale(3.0f);
	character->addChild(dot, 3);

	Sprite* arm = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_ARM);
	arm->setPosition(Vec2(29.5f, 45.0f));
	arm->setAnchorPoint(Point(0.5f, 0.4f));
	character->addChild(arm, -1);

	Sprite* ufo = Sprite::create(FileStuff::ENEMY);
	ufo->setPosition(Vec2(160, 360));
	
	///////////////////////// animations //////////////////////////
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
		DelayTime::create(23 * 0.1f),
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
	bullet->setPosition(character->getPosition() + Vec2(0.0f, 20.0f));
	bullet->setScale(2.0f);
	bullet->setOpacity(0);
	addChild(bullet);
	
	////////////////////////// actions //////////////////////////

	float timeLine = 0.5f;

	Sequence* rotateArm = Sequence::create(
		DelayTime::create(timeLine),
		RotateBy::create(0.4f, -35),
		DelayTime::create(0.2f),
		RotateBy::create(0.4f, 65),
		DelayTime::create(0.3f),
		RotateBy::create(0.4f, -40),
		nullptr);

	Sequence* rototeLine = rotateArm->clone();

	Sequence* moveHorizontallyDot = Sequence::create(
		DelayTime::create(timeLine),
		MoveBy::create(0.4f, Vec2(-37, 0)),
		DelayTime::create(0.2f),
		MoveBy::create(0.4f, Vec2(62,0)),
		DelayTime::create(0.3f),
		MoveBy::create(0.4f, Vec2(-40,0)),
		nullptr);

	timeLine += 3.0f;

	Sequence* shrinkLine = Sequence::create(
		DelayTime::create(timeLine),
		ScaleTo::create(0.4f, 0.7f),
		DelayTime::create(0.2f),
		ScaleTo::create(0.4f, 1.5f),
		DelayTime::create(0.3f),
		ScaleTo::create(0.4f, 1.0f),
		nullptr);

	Sequence* moveVerticallyDot = Sequence::create(
		DelayTime::create(timeLine),
		MoveBy::create(0.4f, Vec2(0, -20)),
		DelayTime::create(0.2f),
		MoveBy::create(0.4f, Vec2(0, 55)),
		DelayTime::create(0.3f),
		MoveBy::create(0.4f, Vec2(0, -35)),
		nullptr);

	timeLine += 3.0f;

	Sequence* removeDot = Sequence::create(
		DelayTime::create(timeLine),
		RemoveSelf::create(),
		nullptr);

	Sequence* removeLine = removeDot->clone();

	Sequence* shootBullet = Sequence::create(
		DelayTime::create(timeLine),
		CallFunc::create(CC_CALLBACK_0(TutorialScene::PlaySoundEffect, this, FileStuff::SOUND_FIREWORK_FLYING)),
		FadeIn::create(0.0f),
		MoveTo::create(2.0f, ufo->getPosition() - Vec2(5, 25)),
		DelayTime::create(0.15f),
		RemoveSelf::create(true),
		nullptr);

	timeLine += 2.15f;

	Sequence* explode = Sequence::create(
		DelayTime::create(timeLine),
		CallFunc::create(CC_CALLBACK_0(TutorialScene::PlaySoundEffect, this, FileStuff::SOUND_FIREWORK_EXPLOSION)),
		CallFunc::create(CC_CALLBACK_0(TutorialScene::PlayExplosion, this, ufo->getPosition() - Vec2(5, 25))),
		nullptr);

	timeLine += 0.8f;

	Sequence* destructUFO = Sequence::create(
		DelayTime::create(timeLine),
		CallFunc::create(CC_CALLBACK_0(TutorialScene::PlaySoundEffect, this, FileStuff::SOUND_UFO_EXPLODE_DEFAULT)),
		destructAnimation,
		removeAfterAnimation,
		nullptr);

	timeLine += 4.0f;

	Sequence* changeToStageScene = Sequence::create(
		DelayTime::create(timeLine),
		CallFunc::create(CC_CALLBACK_0(TutorialScene::ChangeToProperScene, this)),
		nullptr);

	arm->runAction(rotateArm);
	line->runAction(rototeLine);
	dot->runAction(moveHorizontallyDot);

	line->runAction(shrinkLine);
	dot->runAction(moveVerticallyDot);

	line->runAction(removeLine);
	dot->runAction(removeDot);

	bullet->runAction(RepeatForever::create(bullet_animate));
	bullet->runAction(shootBullet);
	
	runAction(explode);
	
	ufo->runAction(destructUFO);
	
	runAction(changeToStageScene);

	return true;
}

void TutorialScene::PlaySoundEffect(const char* fileName)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(fileName);
}

void TutorialScene::PlayExplosion(const Vec2& pos)
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

void TutorialScene::ChangeToProperScene()
{
	if (!cameFromStageScene)
	{
		Director::getInstance()->popScene();
		return;
	}
	Scene* scene = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(scene->getChildByName("GameScene"));
	
	GameManager* gameManager = GameManager::GetInstance();
	gameManager->SetUILayer(gameScene->GetUILayer());
	gameManager->SetGameLayer(gameScene->GetGameLayer());
	gameManager->SetStage(1);

	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);
	Director::getInstance()->replaceScene(scene);
}
