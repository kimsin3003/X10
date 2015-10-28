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
	if (!Layer::init())
	{
		return false;
	}

	auto GotoMainScene = MenuItemFont::create("Go to MainScene", CC_CALLBACK_1(JWScene::ChangeToMainScene, this));
	auto GotoMainSceneMenu = Menu::create(GotoMainScene, NULL);
	GotoMainSceneMenu->setPosition(200, 200);
	this->addChild(GotoMainSceneMenu);
	
	auto myTTFLabel = Label::createWithTTF("This is my TTF", "fonts/arial.ttf", 24);
	myTTFLabel->setPosition(Point(200, 200));
	this->addChild(myTTFLabel);

	this->addChild(sling.Stick);
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

	sling.Shooter->runAction(action_run);

	return true;
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
	if (rect.containsPoint(ClickPoint))
	{
		sling.Stick->setPosition(mouseEvent->getCursorX(), mouseEvent->getCursorY());
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
