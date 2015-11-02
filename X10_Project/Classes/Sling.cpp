#include "stdafx.h"
#include "Sling.h"

Sling* Sling::createSling()
{
	Sling* sling = Sling::create();

	sling->addChild(sling->Stick, 2);
	sling->addChild(sling->Shooter, 1);

	return sling;
}

bool Sling::init()
{
	this->setPosition(200, 160);
	Stick = Sprite::create("firework_stick 33x115.png");
	Stick->setPosition(0, -30);
	Stick->setScale(0.5);

	Shooter = Sprite::create("firework_shooter 6x67.png");
	Shooter->setPosition(0, -60);
	Shooter->setAnchorPoint(Point(0.5, 1));
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

	if (posStartClick.y < this->getPosition().y + 100 &&
		posStartClick.y > this->getPosition().y -100 && 
		posStartClick.x < this->getPosition().x + 100 &&
		posStartClick.x > this->getPosition().x - 100)
	{
		this->setColor(Color3B::GREEN);
		isPressed = true;
	}
}

void Sling::onMouseMove(cocos2d::Event* event)
{
	if (isPressed)
	{
		auto mouseEvent = static_cast<EventMouse*>(event);
		Point ClickPoint = Point(mouseEvent->getCursorX(), mouseEvent->getCursorY());
		Point posChange = ClickPoint - posStartClick;

		if (ClickPoint.y < ShooterUIBoundaryHeight &&
			ClickPoint.x < ShooterUIBoundaryRight &&
			ClickPoint.x > ShooterUIBoundaryLeft)
		{
			float distance = ClickPoint.getDistance(posStartClick);
			float diffX = ClickPoint.x - this->getPosition().x;
			angle.x = -diffX;
			float diffY = ClickPoint.y - this->getPosition().y;
			angle.y = -diffY;
			float angleRadian = atan2f(diffY, diffX);
			float angleOffSet = CC_RADIANS_TO_DEGREES(angleRadian) + 90;
			this->setRotation(-angleOffSet);

			Shooter->setScaleY(distance/Shooter->getContentSize().height);
		}
	}
}

void Sling::onMouseUp(cocos2d::Event* event)
{
	if (isPressed)
	{
		auto mouseEvent = static_cast<EventMouse*>(event);

		//힘과 각도를 계산
		power = 1;

		//원상태로 돌린다
		auto action_0 = RotateTo::create(0.25f, 0);
		auto action_0E = EaseInOut::create(action_0, 1.0f);
		auto action_1 = ScaleTo::create(0.25f, 0.5f);
		auto action_1E = EaseInOut::create(action_1, 1.0f);

		this->runAction(action_0E);
		Shooter->runAction(action_1E);

		//플래그 업데이트
		isPressed = false;
		isShooted = true;

	}
}
