#include "stdafx.h"
#include "GameScene.h"
#include "Bullet.h"
#include "Mirror.h"
#include "Target.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Sling.h"

Scene* GameScene::createScene()
{
	Scene* scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
	{
		return false;
	}
	bulletLayer = Layer::create();
	bullet = Bullet::create();
	bulletLayer->addChild(bullet);
	sling = Sling::createSling(); 
	
	this->addChild(bulletLayer);
	this->addChild(sling);
	CCLOG("x:%d", sling->getPosition().x);
	CCLOG("y:%d", sling->getPosition().y);
	bullet->setPosition(Vec2(sling->getPosition().x, sling->getPosition().y + 40));

	sling->setName("sling");
	
	auto Mouse = EventListenerMouse::create();
	Mouse->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
	Mouse->onMouseUp = CC_CALLBACK_1(GameScene::onMouseUp, this);
	Mouse->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Mouse, this);

	targetList.push_back(Mirror::create());

	for (auto& target : targetList){
		this->addChild(target);
	}

	this->scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	static Target* before = nullptr;
	Target* target;
	//CCLOG("out");
	if (bullet->IsAlive()){
		bullet->Move(Vec2(bullet->GetDirection().x, bullet->GetDirection().y));
		this->unscheduleUpdate();
		if ((target = CheckHit()) && (target != before)){
			HitOperator(target);
			before = target;
		}
		this->scheduleUpdate();
	}
}

Target* GameScene::CheckHit()
{
	Rect bulletBoundingBox = bullet->getBoundingBox();
	Rect targetBoundingBox;

	//CCLOG("in");
	for (auto& target : targetList){
		targetBoundingBox = target->getBoundingBox();
		if (bulletBoundingBox.intersectsRect(targetBoundingBox)){
			
			CCLOG("%p", target);
			return target;
		}
	}

	return NULL;
}

void GameScene::HitOperator(Target* target)
{

	CCLOG("in");
	target->SetEffect(*bullet);
}


void GameScene::onMouseDown(cocos2d::Event* event)
{
	if (sling == nullptr)
		return;

	sling->onMouseDown(event);
}

void GameScene::onMouseUp(cocos2d::Event* event)
{
	if (sling == nullptr)
		return;

	sling->onMouseUp(event);

	if (sling->IsShooted())
	{
		bullet->Start(sling->angle, sling->power);
		sling->isShooted = false;
		bullet->SetAlive(true);

		auto destroyTimer = DelayTime::create(5.0);
		auto callbackBoom = CallFuncN::create(
			CC_CALLBACK_1(GameScene::bulletBoom, this, (void*)&bullet->getPosition())
			);
		auto action = Sequence::create( destroyTimer, callbackBoom, NULL);

		bullet->runAction(action);
	}
}

void GameScene::bulletBoom(Node* b, void* pos)
{
	if (b == nullptr)
		return;
	auto vec = (Vec2*)pos;

	auto bullet = (Bullet*)b;
	bullet->boom((Scene*)this, Point(*vec));
}

void GameScene::onMouseMove(cocos2d::Event* event)
{
	if (sling == nullptr)
		return;

	sling->onMouseMove(event);
}
