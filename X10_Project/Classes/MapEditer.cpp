#include "stdafx.h"
#include "MapEditer.h"

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

	Sprite* background = Sprite::create(FileStuff::BACKGROUND_BOTTOM);
	float scale = (Director::getInstance()->getVisibleSize().width) / (background->getContentSize().width);
	background->setAnchorPoint(Point::ZERO);
	background->setScale(scale);
	this->addChild(background);

	Sling* sling = Sling::create();
	this->addChild(sling);

	EventListenerMouse* mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(MapEditer::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(MapEditer::OnMouseScroll, this);
	m_clicked_sprite = nullptr;

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_1(MapEditer::OnKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	m_pressedKey = static_cast<EventKeyboard::KeyCode>(-1);

	MenuItemLabel* saveButton = MenuItemLabel::create(Label::create("Save", FileStuff::FONT_ARIAL, 20));
	saveButton->setPosition(170, 10);
	saveButton->setName("saveButton");
	this->addChild(saveButton);

	MenuItemLabel* playButton = MenuItemLabel::create(Label::create("Play", FileStuff::FONT_ARIAL, 20));
	playButton->setPosition(220, 10);
	playButton->setName("playButton");
	this->addChild(playButton);

	MenuItemLabel* backButton = MenuItemLabel::create(Label::create("Back", FileStuff::FONT_ARIAL, 20));
	backButton->setPosition(270, 10);
	backButton->setName("backButton");
	this->addChild(backButton);

	MenuItemLabel* warning = MenuItemLabel::create(Label::create("If complete making level\nCHANGE FILE NAME", FileStuff::FONT_ARIAL, 15));
	warning->setPosition(200, 40);
	warning->setName("warning");
	this->addChild(warning);

	vector<TargetInfo> infoList;
	string fileName = FileStuff::EDITING_FILENAME;
	
	//load from file
	if (!StageInformation::loadFile(infoList, fileName))
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
			switch (targetInfo.m_name)
			{
			case TargetInfo::BUBBLE:
				sprite = Sprite::create(FileStuff::BUBBLE);
				break;

			case TargetInfo::ENEMY:
				sprite = Sprite::create(FileStuff::ENEMY);
				break;

			case TargetInfo::MIRROR:
				sprite = Sprite::create(FileStuff::MIRROR);
				break;

			case TargetInfo::VIRTICAL_MIRROR:
				sprite = Sprite::create(FileStuff::VIRTICAL_MIRROR);
				break;

			case TargetInfo::STAR:
				sprite = Sprite::create(FileStuff::BRICK);
				break;
			default:
				sprite = Sprite::create(FileStuff::ENEMY); //default sprite
			}

			sprite->setTag(targetInfo.m_name);
			point = Point(targetInfo.m_position.x, targetInfo.m_position.y);
			sprite->setPosition(point);
			sprite->setRotation(targetInfo.m_rotation);
			sprite->setScaleX(targetInfo.m_scale.x);
			sprite->setScaleY(targetInfo.m_scale.y);
			
			if (sprite)
			{
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

	GameManager* gameManager = GameManager::GetInstance();
	gameManager->SetUILayer(gameScene->GetUILayer());
	gameManager->SetGameLayer(gameScene->GetGameLayer());
	gameManager->SetStage(stageNum);

	TransitionFade* sceneWithEffect = TransitionFade::create(1.5f, scene);

	Director::getInstance()->pushScene(sceneWithEffect);
}

void MapEditer::LeftMouseDown(EventMouse* event)
{
	Sprite* sprite = nullptr;

	if (this->getChildByName("saveButton")->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY())))
	{
		Save();
		return;
	}

	if (this->getChildByName("playButton")->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY())))
	{
		GotoStage(this, 0);
		return;
	}

	if (this->getChildByName("backButton")->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY())))
	{
		Director::getInstance()->replaceScene(MainScene::createScene());
		return;
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

	case EventKeyboard::KeyCode::KEY_S:
		sprite = Sprite::create(FileStuff::BRICK);
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
	m_clicked_sprite = nullptr;
}

void MapEditer::WheelDown(EventMouse* event)
{
	Vector<Node*>& children = m_layer->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		Node* child = children.at(i);
		if (child->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY())))
		{
			int rotation = (int)child->getRotation() + 45;
			//if (rotation >= 0)
				child->setRotation(rotation % 360);
// 			else
// 				child->setRotation(rotation % 360 + 360);
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
		int rotation = m_clicked_sprite->getRotation();
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
		case EventKeyboard::KeyCode::KEY_MINUS:
			m_clicked_sprite->setRotation((rotation-5) % 360);
			break;
		case EventKeyboard::KeyCode::KEY_EQUAL:
			m_clicked_sprite->setRotation((rotation+5) % 360);
			break;

		}
	}
}

void MapEditer::Save()
{
	StageInformation* stInfo = new StageInformation(0);
	stInfo->MakeJsonFileFromLayer(m_layer);
}
