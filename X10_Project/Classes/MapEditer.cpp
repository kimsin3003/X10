#include "stdafx.h"
#include "MapEditer.h"
#include "MapEditLayer.h"
#include "StageInformation.h"
#include "Target.h"
#include "FileStuff.h"

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
	
	EventListenerMouse* _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(MapEditer::OnMouseMove, this);
	_mouseListener->onMouseUp = CC_CALLBACK_1(MapEditer::OnMouseUp, this);
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

	return true;


}

void MapEditer::SetCallBackFuncs(){
	
}

void MapEditer::OnMouseMove(Event* event){
	
}

void MapEditer::OnMouseUp(Event* event){

}

void MapEditer::onMouseDown(EventMouse* event){
	CCLOG("mouse down");
	Sprite* sprite = nullptr;

	if(this->getChildByName("saveButton")->getBoundingBox().containsPoint(Vec2(event->getCursorX(), event->getCursorY()))){
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

void MapEditer::OnMouseScroll(Event* event){

}

void MapEditer::OnKeyPressed(EventKeyboard::KeyCode keyCode)
{
	CCLOG("Key Pressed");
	m_pressedKey = keyCode;
}

void MapEditer::Save()
{
	StageInformation* stInfo = new StageInformation(0);
	stInfo->MakeJsonFileFromLayer(m_layer);
}
