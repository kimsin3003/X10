#include "stdafx.h"
#include "MainScene.h"
#include "JWScene.h"

Scene* JWScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = JWScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool JWScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,25)))
	{
		return false;
	}
	sling.initSling();

	initBG();
	
	auto GotoMainScene = MenuItemFont::create("Go to MainScene", CC_CALLBACK_1(JWScene::ChangeToMainScene, this));
	auto GotoMainSceneMenu = Menu::create(GotoMainScene, NULL);
	GotoMainSceneMenu->setPosition(100, 200);
	this->addChild(GotoMainSceneMenu);

	this->addChild(sling.Shooter);
	sling.Shooter->addChild(sling.Stick);

	auto Mouse = EventListenerMouse::create();
	Mouse->onMouseDown = CC_CALLBACK_1(JWScene::onMouseDown, this);
	Mouse->onMouseUp = CC_CALLBACK_1(JWScene::onMouseUp, this);
	Mouse->onMouseMove = CC_CALLBACK_1(JWScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);

	Sprite* spr = Sprite::create();
	//애니매이션 프레임 추가
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			animFrames.pushBack(SpriteFrame::create("res/animSprite1.png", Rect(i * 31, j * 49, 31, 49)));
		}
	}

	// create the animation out of the frameㄴ
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);

	// run it and repeat it forever
	RepeatForever *action = RepeatForever::create(animate);
	this->addChild(spr);
	spr->runAction(action);
	spr->setPosition(100, 100);
	return true;
}

void JWScene::initBG()
{
	auto winSize = Director::getInstance()->getWinSize();

	auto bgLayer = Layer::create();
	this->addChild(bgLayer);

	auto spr01 = Sprite::create("sky.jpg");
	spr01->setAnchorPoint(Point::ZERO);
	spr01->setPosition(Point::ZERO);
	bgLayer->addChild(spr01, 2);

	auto spr02 = Sprite::create("sky.jpg");
	spr02->setAnchorPoint(Point::ZERO);
	spr02->setPosition(Point(500, 0));
	bgLayer->addChild(spr02, 1);

	auto action_0 = MoveBy::create(3.0, Point(-500, 0));
	auto action_1 = Place::create(Point::ZERO);
	auto action_2 = Sequence::create(action_0, action_1, NULL);
	auto action_3 = RepeatForever::create(action_2);

	bgLayer->runAction(action_3);
}

void JWScene::ChangeToMainScene(Ref* pSender)
{
	Director::getInstance()->replaceScene(MainScene::createScene());
}

void JWScene::onMouseDown(cocos2d::Event* event)
{
	sling.onMouseDown(event);
}

void JWScene::onMouseUp(cocos2d::Event* event)
{
	sling.onMouseUp(event);
}

void JWScene::onMouseMove(cocos2d::Event* event)
{
	sling.onMouseMove(event);
}
