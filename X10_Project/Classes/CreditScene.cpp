#include "stdafx.h"
#include "ConstVars.h"
#include "FileStuff.h"
#include "CreditScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

float CreditScene::ypos = 0.0f;

Scene* CreditScene::createScene()
{
	Scene* scene = Scene::create();

	Layer* layer = CreditScene::create();
	scene->addChild(layer);

	return scene;
}

bool CreditScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	UserDefault::getInstance()->setBoolForKey("AllCleared", true);

	Sprite* credit = Sprite::create();
	credit->addChild(createSentence("Quite Night", 40));
	credit->addChild(createSentence("NEXT INSTITUTE", 20));
	credit->addChild(createSentence("GameDevelopment track", 20));
	credit->addChild(createSentence("Experience project", 20));
	credit->addChild(createSentence("MC Kim", 30));
	credit->addChild(createSentence("JW Choi", 30));
	credit->addChild(createSentence("TW Kim", 30));
	credit->addChild(createSentence(" ", 20));
	credit->addChild(createSentence("Mentor", 30));
	credit->addChild(createSentence("Prof. SM Koo", 20));
	credit->addChild(createSentence("Prof. HS Seo", 20));
	credit->addChild(createSentence(" ", 20));
	credit->addChild(createSentence("Contributor", 30));
	credit->addChild(createSentence(" ", 20));
	credit->addChild(createSentence("HY Nam", 20));
	credit->addChild(createSentence("SB Kim", 20));
	credit->addChild(createSentence(" ", 20));
	
	credit->addChild(createSentence("Game Architecture", 30));
	credit->addChild(createSentence("TW Kim", 20));
	credit->addChild(createSentence("MC Kim", 20));
	credit->addChild(createSentence("JW Choi", 20));
	credit->addChild(createSentence(" ", 20));
	
	credit->addChild(createSentence("Design", 30));
	credit->addChild(createSentence("TW Kim", 20));
	credit->addChild(createSentence("MC Kim", 20));
	credit->addChild(createSentence("JW Choi", 20));
	credit->addChild(createSentence(" ", 20));


	addChild(credit);
	Size size = Director::getInstance()->getVisibleSize();
	credit->setPosition(size.width / 2, 200);

	MoveBy* moveUp = MoveBy::create(2.0, Vec2(0, 40));
	RepeatForever* action = RepeatForever::create(moveUp);
	credit->runAction(action);

	float endTime = 10.0f;
	Sequence* seq = Sequence::create(
		DelayTime::create(endTime),
		CallFunc::create(CC_CALLBACK_0(CreditScene::EndScene, this)),
		nullptr
		);
	return true;
}

void CreditScene::EndScene()
{
	Director::getInstance()->replaceScene(MainScene::createScene());
	return;
}

Node* CreditScene::createSentence(string str, float fontSize)
{
	ypos -= fontSize * 2;
	Node* result = Label::create(str, "arial", fontSize);
	result->setPosition(0, ypos);
	return result;
}