#include "stdafx.h"
#include "MapEditer.h"
#include "MapEditLayer.h"
#include "StageInformation.h"
#include "Target.h"
#include "FileStuff.h"
#include "Sling.h"
#include "MainScene.h"

Scene* MapEditer::createScene()
{
	Scene* scene = Scene::create();

	MapEditer* layer = MapEditer::create();

	scene->addChild(layer);

	return scene;
}

bool MapEditer::init()
{
	if (!Layer::init())
		return false;
	m_layer = Layer::create();
	this->addChild(m_layer, 1);

	Sprite* background = Sprite::create(FileStuff::BACKGROUND);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	this->addChild(background);

	Sling* sling = Sling::create();
	this->addChild(sling);
	
	EventListenerMouse* _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(MapEditer::onMouseDown, this);
	_mouseListener->onMouseScroll = CC_CALLBACK_1(MapEditer::OnMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	EventListenerKeyboard* _keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_1(MapEditer::OnKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
	m_pressedKey = static_cast<EventKeyboard::KeyCode>(-1);

	MenuItemLabel* saveButton = MenuItemLabel::create(Label::create("Save", "res/NanumGothic.ttf", 20));
	saveButton->setPosition(Director::getInstance()->getVisibleSize().width - saveButton->getContentSize().width , saveButton->getContentSize().height);
	saveButton->setName("saveButton");
	this->addChild(saveButton);

	vector<TargetInfo> infoList;
	string fileName = "files/target0.json";
	//load from file
	if (!cppson::loadFile(infoList, fileName))
	{
		CCLOG("Target Load Fail.");
		return true;
	}
	else
	{
		for (TargetInfo targetInfo : infoList)
		{
			
		}
	}
	return true;
}

void MapEditer::LeftMouseDown(EventMouse* event)
{
	Sprite* sprite = nullptr;

	if (this->getChildByName("saveButton")->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY()))){
		Save();
	}

	switch (m_pressedKey){
	case EventKeyboard::KeyCode::KEY_B:
		sprite = Sprite::create(FileStuff::BUBBLE);
		sprite->setTag(TargetInfo::BUBBLE);
		break;

	case EventKeyboard::KeyCode::KEY_C:
		sprite = Sprite::create(FileStuff::CLOUD);
		sprite->setTag(TargetInfo::CLOUD);
		break;

	case EventKeyboard::KeyCode::KEY_E:
		sprite = Sprite::create(FileStuff::ENEMY);
		sprite->setTag(TargetInfo::ENEMY);
		break;

	case EventKeyboard::KeyCode::KEY_M:
		sprite = Sprite::create(FileStuff::MIRROR);
		sprite->setTag(TargetInfo::MIRROR);
		break;

	case EventKeyboard::KeyCode::KEY_V:
		sprite = Sprite::create(FileStuff::VIRTICAL_MIRROR);
		sprite->setTag(TargetInfo::VIRTICAL_MIRROR);
		break;

	case EventKeyboard::KeyCode::KEY_G:
		sprite = Sprite::create(FileStuff::GULL);
		sprite->setTag(TargetInfo::GULL);
		break;

	case EventKeyboard::KeyCode::KEY_S:
		sprite = Sprite::create(FileStuff::STAR_SAD);
		sprite->setTag(TargetInfo::STAR);
		break;
	}

	if (sprite){
		sprite->setPosition(event->getCursorX(), event->getCursorY());
		m_layer->addChild(sprite);
	}
	m_pressedKey = static_cast<EventKeyboard::KeyCode>(-1);
}

void MapEditer::RightMouseDown(EventMouse* event)
{

	Vector<Node*>& children = m_layer->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		Node* child = children.at(i);
		if (child->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY())))
		{
			child->removeFromParent();
			break;
		}
	}
}

void MapEditer::WheelDown(EventMouse* event)
{

	Vector<Node*>& children = m_layer->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		Node* child = children.at(i);
		if (child->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY())))
		{
			child->setRotation(((int)child->getRotation() + 45) % 360);
			break;
		}
	}
}

void MapEditer::onMouseDown(EventMouse* event)
{
	
	if (event->getMouseButton() == 0)
		LeftMouseDown(event);

	else if (event->getMouseButton() == 1)
		RightMouseDown(event);

	else if (event->getMouseButton() == 2)
		WheelDown(event);
	

}

void MapEditer::OnMouseScroll(EventMouse* event)
{
	Vector<Node*>& children = m_layer->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		Node* child = children.at(i);
		if (child->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY())))
		{
			if ((float)event->getScrollY() < 0)
				child->setScale(child->getScale() * 1.1f);
			else
				child->setScale(child->getScale() * 0.9f);
			break;
		}
	}
}

void MapEditer::OnKeyPressed(EventKeyboard::KeyCode keyCode)
{
	m_pressedKey = keyCode;
}

void MapEditer::Save()
{
	StageInformation* stInfo = new StageInformation(0);
	stInfo->MakeJsonFileFromLayer(m_layer);
	Director::getInstance()->replaceScene(MainScene::createScene());
}
