#include "stdafx.h"
#pragma once;
#include "BulletScene.h"
#include "Target.h"
#include "Bullet.h"
#include "Mirror.h"
#include "Enemy.h"

Scene* BulletScene::createScene()
{
	Scene* scene = Scene::create();

	auto layer = BulletScene::create();

	scene->addChild(layer);

	return scene;
}

bool BulletScene::init()
{
	if (!Layer::init())
		return false;

	
	bullet = Bullet::create();
	bullet->setName("Bullet");
	this->addChild(bullet);

	targetList.push_back(Mirror::create());

	for (auto& target : targetList){
		this->addChild(target);
	}

	bullet->Move(Vec2(-0.5, 1));
	this->scheduleUpdate();

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseDown = CC_CALLBACK_1(BulletScene::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	
	
	/*Enemey*/
	auto enemy = Enemy::createEnemy();
	enemy->setName("Enemy");
	enemy->setPosition(Point(115, 100));
	this->addChild(enemy);

	return true;
}

//void Bullet::bulletStart(this, Point psition, Vec2 velocity);


void BulletScene::update(float dt)
{
	static Target* before = nullptr;
	Target* target;

	if (sling->IsShooted()){
		bullet->Move(Vec2(bullet->GetDirection().x, 1));
		CCLOG("out");
		this->unscheduleUpdate();
		if ((target = CheckHit()) && (target != before)){
			CCLOG("in");
			HitOperator(target);
			before = target;
		}
		this->scheduleUpdate();
	}
}

Target* BulletScene::CheckHit()
{
	Rect bulletBoundingBox = bullet->getBoundingBox();
	Rect targetBoundingBox;

	for (auto& target : targetList){
		targetBoundingBox = target->getBoundingBox();
		if (bulletBoundingBox.intersectsRect(targetBoundingBox)){
			
			return target;
		}
	}

	
	return NULL;
}

void BulletScene::HitOperator(Target* target)
{

	CCLOG("in");
	target->SetEffect(*bullet);
}

void BulletScene::onMouseDown(Event *event)
{
	if (event == nullptr)
		return;
	
	auto bulletNode = getChildByName("Bullet");
	if (bullet == nullptr)
		return;

	Bullet* bullet = (Bullet*)bulletNode;
	bullet->boom((Scene*)this, bullet->getPosition());
}
