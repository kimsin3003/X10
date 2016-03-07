#include "stdafx.h"
#include "MainScene.h"
#include "TutorialScene.h"
#include "GameScene.h"
#include "CreditScene.h"
#include "Sling.h"
#include "GameManager.h"
#include "StageScene.h"
#include "IntroScene.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "MapEditer.h"
#include "AdmobHelper.h"
#include <AudioEngine.h>
#include <SimpleAudioEngine.h>

Scene* IntroScene::createScene()
{
    Scene* scene = Scene::create();
    
	IntroScene* layer = IntroScene::create();
	
    scene->addChild(layer);

    return scene;
}

bool IntroScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,0)))
	{
		return false;
	}

	Sequence* seq = Sequence::create(
		DelayTime::create(2.5f),
		CallFuncN::create(CC_CALLBACK_0(IntroScene::WriteText, this, string("Mmm..."), Point(160, 400))),
		DelayTime::create(5.0f),
		CallFuncN::create(CC_CALLBACK_0(IntroScene::WriteText, this, string("Where am I?"), Point(160, 200))),
		DelayTime::create(5.0f),
		CallFuncN::create(CC_CALLBACK_0(IntroScene::WriteText, this, string("...On the road?"), Point(160, 400))),
		DelayTime::create(5.0f),
		CallFuncN::create(CC_CALLBACK_0(IntroScene::WriteText, this, string("It's so quiet..."), Point(160, 200))),
		DelayTime::create(5.0f), 
		CallFuncN::create(CC_CALLBACK_0(IntroScene::ChangeToStageScene, this)),
		nullptr);

	runAction(seq);

	return true;
}


void IntroScene::ChangeToStageScene()
{
	Director::getInstance()->replaceScene(StageScene::createScene());
}

void IntroScene::_FadeOut()
{
	FadeOut* fadeOut = FadeOut::create(2.0f);

	runAction(fadeOut);
}

void IntroScene::RemoveAllChildren()
{
	removeAllChildren();
}

void IntroScene::_FadeIn()
{
	FadeIn* fadeIn = FadeIn::create(2.0f);

	runAction(fadeIn);
}

void IntroScene::WriteText(string text, Point position)
{
	Label* label = Label::createWithTTF(text, FileStuff::FONT_ARIAL, 35, Size(300, 200), TextHAlignment::CENTER, TextVAlignment::CENTER);

	label->setPosition(position);
	label->setOpacity(0.0f);
	FadeIn* fadeIn = FadeIn::create(2.0f);
	FadeOut* fadeOut = FadeOut::create(1.0f);
	Sequence* _blink = Sequence::create(fadeIn,	DelayTime::create(1.0), fadeOut, nullptr);
	addChild(label);
	label->runAction(_blink);
}