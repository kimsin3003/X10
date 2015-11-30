#include "stdafx.h"
#include "Sling.h"
#include "GameManager.h"
#include "ColliderManager.h"
#include "FileStuff.h"


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
	setPosition(Point(205, 53));
	
	//charater set
// 	auto body = Sprite::create("HelloWorld.png");
// 	body->setName("body");
// 	//scale adjustment
// 	Size bodySize = body->getContentSize();
// 	float bodyScale = MIN(WIDTH / bodySize.width, HEIGHT / bodySize.height);
// 	body->setScale(bodyScale);
// 
// 	this->addChild(body);

	/*Make Expect line*/
	for (int i = 0; i < DOTNUM_OF_LINE; i++)
	{
		Sprite* dot = MakeDotOfExpectLine();
		m_expectLine.pushBack(dot);
		dot->setVisible(false);
		this->addChild(dot);
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
		dot->setPosition(m_shotAngle * i);
	}
	/*auto label = Label::create(".","arial", FONT_SIZE);
	auto delay = MoveBy::create(PREDICT_LINE_TIME, m_shotAngle);
	auto action = Sequence::create(delay, RemoveSelf::create(), NULL);
	this->addChild(label);
	label->runAction(action);*/	
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

Sprite* Sling::MakeDotOfExpectLine()
{
	
	Sprite* dot = Sprite::create(FileStuff::SlingLineDot);
	return dot;
}