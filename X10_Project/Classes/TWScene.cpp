#include "stdafx.h"
#include "MainScene.h"
#include "TWScene.h"

Scene* TWScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TWScene::create();

	scene->addChild(layer);

	return scene;
}

bool TWScene::init()
{
	if (!CCLayerColor::initWithColor(Color4B::BLUE))
	{
		return false;
	}


	//1회차 스터디
	auto mainTitle = Label::createWithTTF("Main Title\n fuck!!!!", "fonts/NanumGothic.ttf", 34);
	mainTitle->setPosition(Point(160, 240));
	mainTitle->setName("MainTitle");

	Size winSize = Director::getInstance()->getVisibleSize();
	float labelWidth = mainTitle->getContentSize().width;
	float labelHeight = mainTitle->getContentSize().height;
	auto action1 = MoveTo::create(10.0 / labelHeight, Point(labelWidth / 2, winSize.height - labelHeight / 2));
	auto action2 = MoveTo::create(10.0 / labelWidth, Point(winSize.width - labelWidth / 2, winSize.height - labelHeight / 2));
	auto action3 = MoveTo::create(10.0 / labelHeight, Point(winSize.width - labelWidth / 2, labelHeight / 2));
	auto action4 = MoveTo::create(10.0 / labelWidth, Point(labelWidth / 2, labelHeight / 2));
	auto sequence_action = Sequence::create(action1, action2, action3, action4, NULL);
	auto forever_repeat_action = RepeatForever::create(sequence_action);

	mainTitle->runAction(forever_repeat_action);
	//mainTitle->stopAction(forever_repeat_action);
	this->addChild(mainTitle);

	auto listener = EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(TWScene::onMouseUP, this); 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	//2회차 스터디
	Sprite* character = Sprite::create();
	this->addChild(character);
	character->setPosition(Point(winSize.width / 2, winSize.height / 2));
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	for (int i = 0; i < 4; i++)
		animFrames.pushBack(SpriteFrame::create("res/lisa.png", Rect(0, 48 * i, 27, 48)));

	// create the animation out of the frame
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);

	// run it and repeat it forever
	RepeatForever *action = RepeatForever::create(animate);
	
	character->runAction(action);

	this->schedule(schedule_selector(TWScene::ChangeBackground), 1.0);

	Layer* bgLayer = Layer::create();
	this->addChild(bgLayer, 1);

	auto spr_0 = Sprite::create("res/mc.jpg");
	spr_0->setScaleX(winSize.width);
	spr_0->setScaleY(winSize.height);
	spr_0->setAnchorPoint(Point::ZERO);
	spr_0->setPosition(Point::ZERO);
	bgLayer->addChild(spr_0);

	auto action_0 = MoveBy::create(10.0, Point(-2000, 0));
	auto action_1 = Place::create(Point::ZERO);
	auto action_2 = Sequence::create(action_0, action_1, NULL);
	auto action_3 = RepeatForever::create(action_2);
	bgLayer->runAction(action_3);

	return true;
}

void TWScene::ChangeBackground(float deltaTIme)
{
	Color3B color;
	int rand = random() % 5;
	switch (rand){
	case 0:  
		color = Color3B::YELLOW;
		break;
	case 1:
		color = Color3B::BLUE;
		break;
	case 2:
		color = Color3B::GREEN;
		break;
	case 3:
		color = Color3B::RED;
		break;
	case 4:
		color = Color3B::MAGENTA;
		break;
	case 5:
		color = Color3B::BLACK;
		break;
	case 6:
		color = Color3B::ORANGE;
		break;
	case 7:
		color = Color3B::GRAY;
		break;
	}
	this->setColor(color);
}

void TWScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void TWScene::onMouseUP(cocos2d::Event* event)
{
	auto mainTitle = this->getChildByName("MainTitle");
	if (!mainTitle->isVisible())
		mainTitle->setVisible(true);
	else
		mainTitle->setVisible(false);
}
