#include "stdafx.h"
#include "Sling.h"
#include "GameManager.h"
#include "ColliderManager.h"
#include "FileStuff.h"

Sling::Sling() : m_expectLine(), m_shotAngle(Vec2(0, 0)), m_shotPower(0)
{
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

	//set position of character
	setPosition(SLING_POSITION);
	
	//charater set
	Sprite* character = Sprite::create(FileStuff::CHARACTER_HARDPIXEL);
	character->setScale(SLING_SCALE);
	addChild(character, 2.0);

	/*Make Expect line*/
	for (int i = 0; i < DOTNUM_OF_LINE; i++)
	{
		Sprite* dot = Sprite::create(FileStuff::SLING_LINE_DOT);
		m_expectLine.pushBack(dot);
		float r = -((2.f / DOTNUM_OF_LINE)*(2.f / DOTNUM_OF_LINE) * (i*1.f - DOTNUM_OF_LINE / 2.f) * (i*1.f - DOTNUM_OF_LINE / 2.f)) +1;
		dot->setOpacity(r*180);
		dot->setScale(r*2);
		dot->setVisible(false);
		addChild(dot, 1.0);
	}

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

Point Sling::GetStartLocation()
{
	return getPosition();
}

void Sling::PullStart(Event* e)
{
	if (m_status != STATUS::LOADED)
	{
		return;
	}

	/*Pull mouse 위치 거리 조건 설정 */
	EventMouse* evMouse = static_cast<EventMouse*>(e);
	Point mouseLocation = evMouse->getLocationInView();
	Point startLocation = GetStartLocation();
	float distance = startLocation.getDistance(mouseLocation);

	if (distance > CLICK_RANGE)
		return;
	
	ChangeToPulling();
}

void Sling::Pull(Event* e)
{
	if (m_status != STATUS::PULLING)
	{
		return;
	}

	EventMouse* evMouse = static_cast<EventMouse*>(e);
	Point mouseLocation = evMouse->getLocationInView();
	Point startLocation = GetStartLocation();
	
	m_shotAngle = startLocation - mouseLocation;
	if (m_shotAngle.getAngle() <= Vec2::ZERO.getAngle())
	{
		m_shotAngle = Vec2::ZERO;
		return;
	}

	m_shotPower = startLocation.getDistance(mouseLocation);
	if (m_shotPower > MAX_POWER)
	{	
		m_shotAngle = m_shotAngle / (m_shotPower / MAX_POWER);
		m_shotPower = MAX_POWER;
	}

	/*Set Position expect line */
	for (int i = 0; i < m_expectLine.size(); i++)
	{
		Sprite* dot = m_expectLine.at(i);
		dot->setPosition(m_shotAngle *m_shotPower/MAX_POWER * i);
	}
}


void Sling::Shot(Event* e)
{
	if (m_status != STATUS::PULLING)
	{
		return;
	}

	if (m_shotAngle.getAngle() <= Vec2::ZERO.getAngle())
	{
		m_shotAngle = Vec2::ZERO;
		m_status = STATUS::LOADED;
		for (int i = 0; i < m_expectLine.size(); i++)
		{
			Sprite* dot = m_expectLine.at(i);
			dot->setVisible(false);
		}
		return;
	}

	//fix shot angle,power from last pointer position.
	Pull(e);

	ChangeToShotted();
	GameManager* gm = GameManager::GetInstance();
	gm->ShotBullet(this);
	
}

Vec2 Sling::GetDirection()
{
	return m_shotAngle;
}

float Sling::GetAngleInRadian()
{
	return m_shotAngle.getAngle();
}

float Sling::GetRotationAngle()
{
	return -GetAngleInRadian() / 3.14 * 180 + 90;
}

float Sling::GetSpeed()
{
	return m_shotPower;
}

bool Sling::IsShotted() // --> 쐈는지 체크
{
	if (m_status == STATUS::SHOTTED)
		return true;
	else
		return false;
}

void Sling::ChangeToLoaded() //empty -> load
{
	if (m_status != STATUS::EMPTY)
		return;
	m_status = STATUS::LOADED;
}

void Sling::ChangeToPulling() //loaded -> pulling
{
	if (m_status != STATUS::LOADED)
		return;
	m_status = STATUS::PULLING;
	
	for (Sprite* dot : m_expectLine)
	{
		dot->setVisible(true);
	}
}

void Sling::ChangeToShotted() //pullig -> shotted
{
	if (m_status != STATUS::PULLING)
		return;
	m_status = STATUS::SHOTTED;

	for (Sprite* dot : m_expectLine)
	{
		dot->setVisible(false);
	}
}

void Sling::ChangeToEmpty() //shotted -> empty
{
	m_status = STATUS::EMPTY;
}
