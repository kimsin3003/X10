#include "stdafx.h"
#include "Sling.h"

Sling* Sling::instance = nullptr;
bool Sling::isExist = false;

Sling* Sling::GetInstance()
{
	if (instance == nullptr || isExist == false){ ///# 중괄호 코딩 컨벤션

		///# instance가 존재하는데 isExist가 false면 메모리 누수?
		instance = Sling::create();
		isExist = true;
	}
	return instance;
}


bool Sling::init()
{
	if (Node::init() == false)
	{
		return false;
	}
	//set Name
	setName("Sling");

	//set Empey status
	ChangeToEmpty();

	//set some frame work variable
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//set position low center position
	setPosition(Point(visibleSize.width/2, YPOS));
	
	//charater set
	auto body = Sprite::create("HelloWorld.png");
	body->setName("body");
	//scale adjustment
	Size bodySize = body->getContentSize();
	float bodyScale = MIN(WIDTH / bodySize.width, HEIGHT / bodySize.height);
	body->setScale(bodyScale);

	this->addChild(body);
	
	EventListenerMouse* _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(Sling::Shot, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(Sling::PullStart, this);
	_mouseListener->onMouseMove = CC_CALLBACK_1(Sling::Pull, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	return true;
}

void Sling::Reset() // --> 매스테이지마다 리셋. 매개변수는 미정.
{
	ChangeToEmpty();
}

void Sling::ShotComplete()
{
	ChangeToEmpty();
}
void Sling::LoadBullet()
{
	ChangeToLoaded();
}

void Sling::PullStart(Event* e)
{
	if (status != STATUS::LOADED)
	{
		return;
	}

	/*Pull mouse 위치 거리 조건 설정 */
	EventMouse* evMouse = (EventMouse*)e; ///# c++ 캐스팅을 써라.
	Point mouseLocation = evMouse->getLocationInView();
	Point startLocation = GetStartLocation();
	float distance = startLocation.getDistance(mouseLocation);
	if (distance > CLICKABLE_RANGE)
		return;

	ChangeToPulling();
}

void Sling::Pull(Event* e)
{
	if (status != STATUS::PULLING)
	{
		return;
	}

	EventMouse* evMouse = (EventMouse*)e;
	Point mouseLocation = evMouse->getLocationInView();
	Point startLocation = GetStartLocation();
	
	shotAngle = startLocation - mouseLocation;
	if (shotAngle.getAngle() < Vec2::ZERO.getAngle())
	{
		//밑으로 각도가 한계를 넘어가는 것들 수정하는 부분..
		//아직 안만듬
	}

	shotPower = startLocation.getDistance(mouseLocation);
	if (shotPower > MAX_POWER)
	{	
		shotAngle = shotAngle / (shotPower / MAX_POWER);
		shotPower = MAX_POWER;
	}

	auto label = Label::create(".","arial", FONT_SIZE);
	auto delay = MoveBy::create(PREDICT_LINE_TIME, shotAngle);
	auto action = Sequence::create(delay, RemoveSelf::create(), NULL);
	this->addChild(label);
	label->runAction(action);	
}

Point Sling::GetStartLocation()
{
	return getPosition();
}

void Sling::Shot(Event* e)
{
	if (status != STATUS::PULLING)
	{
		return;
	}

	//fix shot angle,power from last pointer position.
	Pull(e);

	ChangeToShotted();
}

Vec2 Sling::GetDirection()
{
	return shotAngle;
}

float Sling::GetAngleInRadian()
{
	return shotAngle.getAngle();
}

float Sling::GetRotationAngle()
{
	return -GetAngleInRadian() / 3.14 * 180 + 90;
}

float Sling::GetSpeed()
{
	return shotPower;
}


bool Sling::IsShotted() // --> 쐈는지 체크
{
	if (status == STATUS::SHOTTED)
		return true;
	else
		return false;
}

void Sling::ChangeToLoaded() //empty -> load
{
	if (status != STATUS::EMPTY)
		return;
	status = STATUS::LOADED;
}

void Sling::ChangeToPulling() //loaded -> pulling
{
	if (status != STATUS::LOADED)
		return;
	status = STATUS::PULLING;
}

void Sling::ChangeToShotted() //pullig -> shotted
{
	if (status != STATUS::PULLING)
		return;
	status = STATUS::SHOTTED;
}

void Sling::ChangeToEmpty() //shotted -> empty
{
	status = STATUS::EMPTY;
}
