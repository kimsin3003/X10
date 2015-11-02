#include "stdafx.h"
#include "Bullet.h"
#include "Target.h"
#include "Explosion.h"

bool Bullet::init()
{
	if (!Layer::init())
		return false;
	speed = 1;
	alive = true;
	direction = Vec2(0, 0);
	bullet = Sprite::create("res/bullet.png");
	bullet->setAnchorPoint(Point(0.5, 0.5));
	bullet->setScaleX(0.2);
	bullet->setScaleY(0.2);
	Size windowSize = Director::getInstance()->getVisibleSize();
	bullet->setPosition(Point(windowSize.width / 2, 10));
	//Start(Vec2(0, 1));
	this->addChild(bullet);
	return true;
}

//Vec2's x,y absolute size is less or equal to 1
void Bullet::Move(Vec2 initialDirection)
{
	if (bullet == nullptr)
		return;

	direction = initialDirection;
	MoveBy* action;
	
	if(IsAlive()){
		action = MoveBy::create(duration, direction * speed);
		bullet->runAction(action);
		return;
	}
	bullet->stopAllActions();

}

void Bullet::HitProgress(Target& target)
{
	target.SetEffect(*this);

}


void Bullet::Start(Vec2 direction, float power)
{
	SetSpeed(power);
	Move(direction);

}

void Bullet::boom(Scene* scene, Point p)
{
	Explosion::boom(scene, getPosition());
	this->setVisible(false);
}
