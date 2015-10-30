#include "stdafx.h"
#include "Bullet.h"

Scene* Bullet::createScene()
{
	Scene* scene = Scene::create();

	auto layer = Bullet::create();

	scene->addChild(layer);

	return scene;
}

bool Bullet::init()
{
	if (!Layer::init())
		return false;

	speed = 1;
	alive = true;
	direction = Vec2(0, 0);
	bullet = Sprite::create("res/bullet.png");
	bullet->setAnchorPoint(Point(0.5, 0));
	bullet->setScaleX(0.2);
	bullet->setScaleY(0.2);
	Size windowSize = Director::getInstance()->getVisibleSize();
	bullet->setPosition(Point(windowSize.width / 2, 10));

	this->addChild(bullet);

	Start(Vec2(1, 2));
	return true;
}

//Vec2's x,y absolute size is less or equal to 1
void Bullet::Start(Vec2 initialDirection)
{
	direction = initialDirection;
	MoveBy* action = MoveBy::create(1.0, direction * speed);
	
	while (IsAlive()){
		bullet->runAction(action);
		action = MoveBy::create(1.0, direction * speed);

		UpdateState();
	}

}

void Bullet::UpdateState()
{

	if (!HitCheck()){
		return;
	}


	
}

bool Bullet::HitCheck()
{
	throw std::logic_error("The method or operation is not implemented.");
}
