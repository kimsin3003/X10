#include "stdafx.h"
#include "Sling.h"

Sling* Sling::instance = nullptr;
bool Sling::isExist = false;

Sling* Sling::GetInstance()
{
	if (instance == nullptr || isExist == false){
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
void Sling::NewBulletLoad()
{
	ChangeToLoaded();
}

void Sling::PullStart(Event* e)
{
	if (status != loaded)
	{
		return;
	}

	//
	/*이곳에 Pull mouse 위치 조건 설정 할 수 있음.*/
	//
	ChangeToPulling();
}


void Sling::Pull(Event* e)
{
	if (status != pulling)
	{
		return;
	}
	EventMouse* evMouse = (EventMouse*)e;
	Point mouseLocation = evMouse->getLocation();
	Point startLocation = getStartLocation();
	
	shootAngle = mouseLocation - startLocation;
	if (shootAngle.getAngle() < Vec2::ZERO.getAngle())
	{
		//밑으로 각도가 한계를 넘어가는 것들 수정하는 부분..
	}
	shootPower = startLocation.getDistance(mouseLocation);

	ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
	ccDrawLine(ccp(0, 0), ccp(100, 100));

	//auto draw_node = DrawNode::create();
	//draw_node->drawLine(Point(0, 0), Point(100, 100), Color4F(255,255,255,255));
	auto label = Label::create(".","arial", 24);
	auto delay = MoveBy::create(0.5, shootAngle);
	auto action = Sequence::create(delay, RemoveSelf::create(), NULL);
	label->runAction(action);
	this->addChild(label);
}

Point Sling::GetStartLocation()
{
	return getPosition();
}

void Sling::Shot(Event* e)
{
	if (status != pulling)
	{
		return;
	}
	//fix shot angle,power from last pointer position.
	Pull(e);

	ChangeToShooted();
}

bool Sling::IsShoted() // --> 쐈는지 체크
{
	if (status == shoted)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

Vec2 Sling::GetDirection()
{
	return shootAngle;
}

float Sling::GetSpeed()
{
	return shootPower;
}


void Sling::ChangeToLoaded() //empty -> load
{
	if (status != empty)
		return;
	status = loaded;
}
void Sling::ChangeToPulling() //loaded -> pulling
{
	if (status != loaded)
		return;
	status = pulling;
}
void Sling::ChangeToShooted() //pullig -> shooted
{
	if (status != pulling)
		return;
	status = shoted;
}
void Sling::ChangeToEmpty() //shooted -> empty
{
	status = empty;
	ChangeToLoaded();
}
