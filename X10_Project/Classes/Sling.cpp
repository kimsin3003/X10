#include "stdafx.h"
#include "Sling.h"

Sling* Sling::createSling(Bullet* bullet)
{
	Sling* sling = Sling::create();
	
	sling->addChild(bullet, 3);
	sling->addChild(sling->Stick, 2);
	sling->addChild(sling->Shooter, 1);

	bullet->setPosition(Point(0, 130));

	return sling;
}

bool Sling::init()
{
	this->setPosition(200, 0);

	Stick = Sprite::create("firework_stick 33x115.png");
	Stick->setPosition(0, 150);
	Stick->setScale(0.5);

	Shooter = Sprite::create("firework_shooter 6x67.png");
	Shooter->setPosition(0, 100);
	Shooter->setScale(0.5);

	angle = Point::ZERO;
	power = 0;
	
	isPressed = false;
	isShooted = false;

	return true;
}

void Sling::onMouseDown(cocos2d::Event* event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);
	
	posStartClick = Point(mouseEvent->getCursorX(), mouseEvent->getCursorY());

	isPressed = true;
}

void Sling::onMouseMove(cocos2d::Event* event)
{
	if (isPressed && posStartClick.y < ShooterUIBoundary)
	{
		auto mouseEvent = static_cast<EventMouse*>(event);
		Point ClickPoint = Point(mouseEvent->getCursorX(), mouseEvent->getCursorY());
		Point posChange = ClickPoint - posStartClick;

		int rotateDegree = (int)(posChange.x)%180;
		
		int powerDegreeX = posChange.x;
		int powerDegereY = posChange.y;

		if (rotateDegree > 90)
			rotateDegree = 90;
		else if (rotateDegree < -90)
			rotateDegree = -90;
		
		auto sling = (Sling*)Shooter->getParent();
		
		sling->setRotation(-rotateDegree);
//		Shooter->setScaleX(1);
//		Shooter->setScaleY(1);
	}
}

void Sling::onMouseUp(cocos2d::Event* event)
{
	auto mouseEvent = static_cast<EventMouse*>(event);

	int powerX = pow(mouseEvent->getCursorX() - Shooter->getPositionX(), 2);
	int powerY = pow(mouseEvent->getCursorY() - Shooter->getPositionY(), 2);
	power = sqrt(powerX + powerY);
	angle = Point(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	isPressed = false;
	isShooted = true;

	Shooter->setRotation(1);
	Shooter->setScaleX(1);
	Shooter->setScaleY(1);
}
