#include "stdafx.h"
#include "IntroScene.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "StageScene.h"
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
		return false;

	UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, 1);

	CallFuncN* text1 = CallFuncN::create(
		CC_CALLBACK_1(IntroScene::Text1, this));

	CallFuncN* text2 = CallFuncN::create(
		CC_CALLBACK_1(IntroScene::Text2, this));

	CallFuncN* removeLetters = CallFuncN::create(
		CC_CALLBACK_1(IntroScene::RemoveAllChildren, this));

	CallFuncN* toStageScene = CallFuncN::create(
		CC_CALLBACK_1(IntroScene::ChangeToStageScene, this));

	Sequence* seq = Sequence::create(
		text1,
		DelayTime::create(10.0f),
		removeLetters,
		text2,
		DelayTime::create(10.0f),
		toStageScene,
		nullptr);

	runAction(seq);
	return true;
}

void IntroScene::Text1(Ref* pSender)
{
	Vec2 deltaPos = Vec2(0, 16.5f);
	Vec2 textPos = Vec2(20.0f, 400.0f);

	PrintIntroText("Why am I standing on a road?", textPos, 1.0f, 1.25f);
	PrintIntroText("Firework? In my Pocket!?", textPos -= deltaPos * 6, 5.5f, 1.25f);
	PrintIntroText("What the..", textPos -= deltaPos * 2, 8.5f, 1.25f);
}

void IntroScene::Text2(Ref* pSender)
{
	Vec2 deltaPos = Vec2(0, 16.5f);
	Vec2 textPos = Vec2(20.0f, 400.0f);

	PrintIntroText("Oh my, Aliens?", textPos, 2.0f, 1.25f);
	PrintIntroText("I've got to get out out of here!", textPos -= deltaPos * 6, 6.5f, 1.25f);
}

void IntroScene::PrintIntroText(const string& message, const Vec2& pos, float startTime, float textScale)
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


void IntroScene::RemoveAllChildren(Ref* pSender)
{
	removeAllChildren();
}

void IntroScene::ChangeToStageScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(StageScene::createScene());
}
