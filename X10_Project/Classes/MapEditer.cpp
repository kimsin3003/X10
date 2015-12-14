#include "stdafx.h"
#include "MapEditer.h"
#include "MapEditLayer.h"
#include "StageInformation.h"
#include "Target.h"
#include "FileStuff.h"
#include "Sling.h"
#include "MainScene.h"
#include "GameScene.h"
#include "GameManager.h"

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
	m_clicked_sprite = nullptr;

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	EventListenerKeyboard* _keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_1(MapEditer::OnKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
	m_pressedKey = static_cast<EventKeyboard::KeyCode>(-1);

	MenuItemLabel* saveButton = MenuItemLabel::create(Label::create("Save", "res/NanumGothic.ttf", 20));
	saveButton->setPosition(170, 10);
	saveButton->setName("saveButton");
	this->addChild(saveButton);

	MenuItemLabel* playButton = MenuItemLabel::create(Label::create("Play", "res/NanumGothic.ttf", 20));
	playButton->setPosition(210, 10);
	playButton->setName("playButton");
	this->addChild(playButton);

	MenuItemLabel* backButton = MenuItemLabel::create(Label::create("Back", "res/NanumGothic.ttf", 20));
	backButton->setPosition(250, 10);
	backButton->setName("backButton");
	this->addChild(backButton);

	MenuItemLabel* warning = MenuItemLabel::create(Label::create("If complete making level\nCHANGE FILE NAME:\n target0.json in files folder", "res/NanumGothic.ttf", 12));
	warning->setPosition(200, 30);
	warning->setName("warning");
	this->addChild(warning);

	vector<TargetInfo> infoList;
	string fileName = FileStuff::EDITING_FILENAME;
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
			Sprite* sprite = nullptr;
			Point point;
			switch (targetInfo.m_name.get()){
			case TargetInfo::BUBBLE:
				sprite = Sprite::create(FileStuff::BUBBLE);
				sprite->setTag(TargetInfo::BUBBLE);
				point = Point(targetInfo.m_position.get().x.get(), targetInfo.m_position.get().y.get());
				sprite->setPosition(point);
				sprite->setRotation(targetInfo.m_rotation.get());
				sprite->setScaleX(targetInfo.m_scale.get().x.get());
				sprite->setScaleY(targetInfo.m_scale.get().y.get());
				break;

			case TargetInfo::CLOUD:
				sprite = Sprite::create(FileStuff::CLOUD);
				sprite->setTag(TargetInfo::CLOUD);
				point = Point(targetInfo.m_position.get().x.get(), targetInfo.m_position.get().y.get());
				sprite->setPosition(point);
				sprite->setRotation(targetInfo.m_rotation.get());
				sprite->setScaleX(targetInfo.m_scale.get().x.get());
				sprite->setScaleY(targetInfo.m_scale.get().y.get());
				break;

			case TargetInfo::ENEMY:
				sprite = Sprite::create(FileStuff::ENEMY);
				sprite->setTag(TargetInfo::ENEMY);
				point = Point(targetInfo.m_position.get().x.get(), targetInfo.m_position.get().y.get());
				sprite->setPosition(point);
				sprite->setRotation(targetInfo.m_rotation.get());
				sprite->setScaleX(targetInfo.m_scale.get().x.get());
				sprite->setScaleY(targetInfo.m_scale.get().y.get());
				break;

			case TargetInfo::MIRROR:
				sprite = Sprite::create(FileStuff::MIRROR);
				sprite->setTag(TargetInfo::MIRROR);
				point = Point(targetInfo.m_position.get().x.get(), targetInfo.m_position.get().y.get());
				sprite->setPosition(point);
				sprite->setRotation(targetInfo.m_rotation.get());
				sprite->setScaleX(targetInfo.m_scale.get().x.get());
				sprite->setScaleY(targetInfo.m_scale.get().y.get());
				break;

			case TargetInfo::VIRTICAL_MIRROR:
				sprite = Sprite::create(FileStuff::VIRTICAL_MIRROR);
				sprite->setTag(TargetInfo::VIRTICAL_MIRROR);
				point = Point(targetInfo.m_position.get().x.get(), targetInfo.m_position.get().y.get());
				sprite->setPosition(point);
				sprite->setRotation(targetInfo.m_rotation.get());
				sprite->setScaleX(targetInfo.m_scale.get().x.get());
				sprite->setScaleY(targetInfo.m_scale.get().y.get());
				break;

			case TargetInfo::GULL:
				sprite = Sprite::create(FileStuff::GULL);
				sprite->setTag(TargetInfo::GULL);
				point = Point(targetInfo.m_position.get().x.get(), targetInfo.m_position.get().y.get());
				sprite->setPosition(point);
				sprite->setRotation(targetInfo.m_rotation.get());
				sprite->setScaleX(targetInfo.m_scale.get().x.get());
				sprite->setScaleY(targetInfo.m_scale.get().y.get());
				break;

			case TargetInfo::STAR:
				sprite = Sprite::create(FileStuff::STAR_SAD);
				sprite->setTag(TargetInfo::STAR);
				point = Point(targetInfo.m_position.get().x.get(), targetInfo.m_position.get().y.get());
				sprite->setPosition(point);
				sprite->setRotation(targetInfo.m_rotation.get());
				sprite->setScaleX(targetInfo.m_scale.get().x.get());
				sprite->setScaleY(targetInfo.m_scale.get().y.get());
				break;
			}
			
			if (sprite){
				m_layer->addChild(sprite);
			}
		}
	}

	return true;
}

void MapEditer::GotoStage(Ref* pSender, int stageNum)
{
	Scene* scene = GameScene::createScene();
	GameScene* gameScene = static_cast<GameScene*>(scene->getChildByName("GameScene"));

	GameManager::GetInstance()->SetStage(gameScene->GetGameLayer(), stageNum);
	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);

	Director::getInstance()->pushScene(sceneWithEffect);
}

void MapEditer::LeftMouseDown(EventMouse* event)
{
	Sprite* sprite = nullptr;

	if (this->getChildByName("saveButton")->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY()))){
		Save();
	}

	if (this->getChildByName("playButton")->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY()))){
		GotoStage(this, 0);
	}

	if (this->getChildByName("backButton")->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY()))){
		Director::getInstance()->replaceScene(MainScene::createScene());
	}

	Vector<Node*>& children = m_layer->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		Node* child = children.at(i);
		if (child->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY())))
		{
			m_clicked_sprite = child;
			return;
		}
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

	if (sprite)
	{
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

	if (m_clicked_sprite)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			m_clicked_sprite->setPosition(m_clicked_sprite->getPosition().x, m_clicked_sprite->getPosition().y + 1);
			break;

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			m_clicked_sprite->setPosition(m_clicked_sprite->getPosition().x + 1, m_clicked_sprite->getPosition().y);
			break;

		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			m_clicked_sprite->setPosition(m_clicked_sprite->getPosition().x, m_clicked_sprite->getPosition().y - 1);
			break;

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			m_clicked_sprite->setPosition(m_clicked_sprite->getPosition().x - 1, m_clicked_sprite->getPosition().y);
			break;

		}
	}
}

void MapEditer::Save()
{
	StageInformation* stInfo = new StageInformation(0);
	stInfo->MakeJsonFileFromLayer(m_layer);
}
