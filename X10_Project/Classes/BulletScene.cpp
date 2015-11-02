#include "stdafx.h"
#pragma once;
#include "BulletScene.h"
#include "Target.h"
#include "Bullet.h"
#include "Mirror.h"

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
	this->addChild(bullet);

	targetList.push_back(Mirror::create());

	for (auto& target : targetList){
		this->addChild(target);
	}

	bullet->Move(Vec2(-0.5, 1));
	this->scheduleUpdate();
	return true;
}

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

