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

	initBG();

	auto GotoMainScene = MenuItemFont::create("Go to MainScene", CC_CALLBACK_1(JWScene::ChangeToMainScene, this));
	auto GotoMainSceneMenu = Menu::create(GotoMainScene, NULL);
	GotoMainSceneMenu->setPosition(100, 200);
	this->addChild(GotoMainSceneMenu);
	
	auto myTTFLabel = Label::createWithTTF("This is my TTF", "fonts/arial.ttf", 24);
	myTTFLabel->setPosition(Point(300, 200));
	this->addChild(myTTFLabel);

	this->addChild(sling.Stick, 1, "LovelyStick");
	this->addChild(sling.Shooter);

	auto Mouse = EventListenerMouse::create();
	Mouse->onMouseDown = CC_CALLBACK_1(JWScene::onMouseDown, this);
	Mouse->onMouseUp = CC_CALLBACK_1(JWScene::onMouseUp, this);
	Mouse->onMouseMove = CC_CALLBACK_1(JWScene::onMouseMove, this);
	Mouse->onMouseScroll = CC_CALLBACK_1(JWScene::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);

	auto go_bottomRight = MoveTo::create(1, Point(300, 0));
	auto go_topRight = MoveTo::create(1, Point(300, 300));
	auto go_topLeft = MoveTo::create(1, Point(0, 300));
	auto go_bottomleft = MoveTo::create(1, Point(0, 0));

	auto action_set = Sequence::create(go_bottomRight, go_topRight, go_topLeft, go_bottomleft, NULL);
	auto action_run = RepeatForever::create(action_set);

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
	RepeatForever *action = RepeatForever::create(animate); //액션을 만들어서
	
	sling.Shooter->runAction(action);

	this->schedule(schedule_selector(JWScene::changeLayerColor), 1.0);

	return true;
}

void JWScene::initBG()
{
	auto winSize = Director::getInstance()->getWinSize();

	auto bgLayer = Layer::create();
	this->addChild(bgLayer);
	bgLayer->setTag(1010);

	auto spr01 = Sprite::create("sky.jpg");
	spr01->setTag(1001);
	spr01->setAnchorPoint(Point::ZERO);
	spr01->setPosition(Point::ZERO);
	bgLayer->addChild(spr01, 2);

	auto spr02 = Sprite::create("sky.jpg");
	spr02->setAnchorPoint(Point::ZERO);
	spr02->setPosition(Point(500, 0));
	spr02->setName("BG");
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
	auto mouseEvent = static_cast<EventMouse*>(event);
	Point ClickPoint = Point(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	auto isRight = mouseEvent->getMouseButton();
	isPressed = true;
	auto rect = sling.Stick->getBoundingBox();
	auto aoao = this->getChildByName("LovelyStick");

	if (rect.containsPoint(ClickPoint))
	{
		aoao->setPosition(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	}
}

void JWScene::onMouseUp(cocos2d::Event* event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);
	Vec2 ClickPoint = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	auto isRight = mouseEvent->getMouseButton();
	isPressed = false;
}

void JWScene::onMouseMove(cocos2d::Event* event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);
	Vec2 ClickPoint = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

	auto rect = sling.Stick->getBoundingBox();
	if (rect.containsPoint(ClickPoint) && isPressed)
	{
		sling.Stick->setPosition(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	}
}

void JWScene::onMouseScroll(cocos2d::Event* event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);
	Vec2 ClickPoint = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
}

void JWScene::changeLayerColor(float delta)
{
	auto parent = (Layer*)this->getChildByTag(1010);
	auto bgSpr = (Sprite*)parent->getChildByTag(1001);

	int r = 0 + rand() % 256;
	int g = 0 + rand() % 256;
	int b = 0 + rand() % 256;
	if (bgSpr != NULL) {
		bgSpr->setColor(Color3B(r, g, b));
	}
}