#include "stdafx.h"
#include "Sling.h"

Sling* Sling::instance = nullptr;

Sling* Sling::GetInstance()
{
	if (instance == nullptr){
		instance = Sling::create();
	}
	return instance;
}

bool Sling::init()
{
	if (Node::init() == false)
	{
		return false;
	}

	ChangeToEmpty();

	//charater anmation start

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
	shootAngle = -(startLocation - mouseLocation);
	if (shootAngle.getAngle() < Vec2::ZERO.getAngle())
	{
	}
	shootPower = startLocation.getDistance(mouseLocation);
}

Point Sling::getStartLocation()
{
	return getPosition();
}

void Sling::Shot(Event* e)
{
	if (status != pulling)
	{
		return;
	}
	//fix shot angle of last pointer position.
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
}
