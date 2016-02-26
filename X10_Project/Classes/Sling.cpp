#include "stdafx.h"
#include "Sling.h"
#include "GameManager.h"
#include "FileStuff.h"

Sling::Sling() : m_shotAngle(Vec2::ZERO), m_shotPower(0), 
				 m_arm(nullptr), m_character(nullptr), 
				 m_status(STATUS::EMPTY) 
{
	m_expectLine.reserve(DOTNUM_OF_LINE);
	m_beforeLine.reserve(DOTNUM_OF_LINE);
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

	/*Make Expect line*/
	for (int i = 0; i < DOTNUM_OF_LINE; i++)
	{
		Sprite* dot = Sprite::create(FileStuff::SLING_LINE_DOT);
		float r = -((2.f / DOTNUM_OF_LINE)*(2.f / DOTNUM_OF_LINE) * (i*1.f - DOTNUM_OF_LINE / 2.f) * (i*1.f - DOTNUM_OF_LINE / 2.f)) + 1;
		dot->setOpacity(r * 100);
		dot->setScale(r * 2);
		dot->setVisible(false);
		m_expectLine.pushBack(dot);
		addChild(dot, 1);
	}
	/*Make Before line*/
	for (int i = 0; i < DOTNUM_OF_LINE; i++)
	{
		Sprite* dot = Sprite::create(FileStuff::SLING_LINE_DOT);
		float r = -((2.f / DOTNUM_OF_LINE)*(2.f / DOTNUM_OF_LINE) * (i*1.f - DOTNUM_OF_LINE / 2.f) * (i*1.f - DOTNUM_OF_LINE / 2.f)) + 1;
		dot->setOpacity(r * 100 * 0.5);
		dot->setScale(r * 2);
		dot->setVisible(false);
		m_beforeLine.pushBack(dot);
		addChild(dot, 1);
	}

	m_arm = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_ARM);
	m_arm->setScale(SLING_SCALE);
	m_arm->setRotation(DEFAULT_ARM);
	m_arm->setAnchorPoint(Point(0.5, 0.4));
	m_arm->setPosition(Vec2(0, 10));
	addChild(m_arm, 1);

	m_character = LoadCharacter();
	addChild(m_character, 2);

	EventListenerTouchOneByOne* touchListener = EventListenerTouchOneByOne::create();
 	touchListener->setSwallowTouches(true);
 	touchListener->onTouchEnded = CC_CALLBACK_2(Sling::Shot, this);
 	touchListener->onTouchBegan = CC_CALLBACK_2(Sling::PullStart, this);
 	touchListener->onTouchMoved = CC_CALLBACK_2(Sling::Pull, this);
 	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void Sling::Reset()
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

Sprite* Sling::LoadCharacter()
{
	Sprite* character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_CACHE);
	character->setPosition(Vec2::ZERO);
	return character;
}

bool Sling::PullStart(Touch* touch, Event* unused_event)
{
	if (m_status != STATUS::LOADED)
	{
		return false;
	}

	/*Pull mouse 위치 거리 조건 설정 */
	Point touchLocation = touch->getLocation();
	Point startLocation = GetStartLocation();
	float distance = startLocation.getDistance(touchLocation);

	
	if (distance > CLICK_RANGE)
	{
		return false;
	}

	Sprite* range = Sprite::create(FileStuff::SLING_RANGE);
	range->setAnchorPoint(Vec2(0.5f, 0));
	range->setScale(1.3f);
	range->setName("range");
	addChild(range, 0);

	m_character->removeFromParent();
	m_character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_SELECTED);

	addChild(m_character, 2);

	ChangeToPulling();
	Pull(touch,unused_event);

	return true;
}

void Sling::Pull(Touch* touch, Event* unused_event)
{
	if (m_status != STATUS::PULLING)
	{
		return;
	}

	Point touchLocation = touch->getLocation();
	Point startLocation = GetStartLocation();
	
	m_shotPower = startLocation.getDistance(touchLocation);
	m_shotAngle = (touchLocation - startLocation) / m_shotPower;
	
	//power가 일정 이상이면 max로 고정
	if (m_shotPower > MAX_POWER)
	{
		m_shotPower = MAX_POWER;
	}

	//angle 이 밑으로 내려가는경우에는 취소.
	if (m_shotAngle.getAngle() <= Vec2::ZERO.getAngle())
	{
		m_shotAngle = Vec2::ZERO;
		return;
	}

	/*Set Position expect line */
	for (int i = 0; i < m_expectLine.size(); i++)
	{
		Sprite* dot = m_expectLine.at(i);
		float dot_interval = m_shotPower / m_expectLine.size() / getScale();
		dot->setPosition(m_shotAngle * dot_interval * (i+1));
	}
	// set rotation arm angle
	m_arm->setRotation(-m_shotAngle.getAngle()*60 + 90);
}


void Sling::Shot(Touch* touch, Event* unused_event)
{
	if (m_status != STATUS::PULLING)
	{
		return;
	}

	getChildByName("range")->removeFromParent();

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
	Pull(touch,unused_event);

	/*Set Position before line */
	for (int i = 0; i < m_beforeLine.size(); i++)
	{
		Sprite* dot = m_beforeLine.at(i);
		float dot_interval = m_shotPower / m_expectLine.size() / getScale();
		dot->setPosition(m_shotAngle * dot_interval * (i + 1));
		dot->setVisible(true);
	}

	ChangeToShotted();

	GameManager* gm = GameManager::GetInstance();
	gm->ShotBullet();

	m_character->removeFromParent();
	m_character = Sprite::createWithSpriteFrameName(FileStuff::CHARACTER_CACHE);
	addChild(m_character, 2);
}

void Sling::RemoveDots()
{
	for (Sprite* dot : m_expectLine)
	{
		dot->removeFromParent();
	}

	for (Sprite* dot : m_beforeLine)
	{
		dot->removeFromParent();
	}
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
