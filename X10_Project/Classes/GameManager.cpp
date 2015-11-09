#include "stdafx.h"

#include "GameManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "Target.h"
#include "Sling.h"
#include "ColliderManager.h"
#include "TargetManager.h"
#include "GameLayer.h"
#include "UILayer.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	sling = Sling::GetInstance();
	colliderManager = ColliderManager::GetInstance();
	targetManager = TargetManager::GetInstance();
}

GameManager::~GameManager()
{

}


GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::Reset()
{
	delete instance;
	instance = new GameManager();
	ColliderManager::GetInstance()->Reset();
}


void GameManager::InitTargets(GameLayer* gameLayer)
{
	Vector<Target*> targets = targetManager->GetTargets();
	for (auto iter = targets.begin(); iter < targets.end(); iter++)
		gameLayer->addChild(*iter);
}

//main game logic
void GameManager::Play(GameLayer* gameLayer, UILayer* uiLayer)
{
	Vector<Collider*> colliders = colliderManager->GetColliders();
	Vector<Target*> targets = targetManager->GetTargets(); 
	//shot if sling shotted the Collider. --> isShotted가 언제 어떻게 바뀌냐에 따라 여기는 바뀌어야할듯.

	if (colliderManager->HasNextCollider())
	{
		sling->NewColliderLoad();
	}

	if (sling->IsShotted())
	{
		Bullet* colliderToShot = (Bullet*)colliderManager->GetColliderToShot();
		colliderToShot->setPosition(sling->getPosition()); //Game manager sets initial bullet position
		colliderToShot->setRotation(sling->GetRotationAngle());
		colliderToShot->SetDirection(sling->GetDirection());
		colliderToShot->SetSpeed(sling->GetSpeed()/20);
		colliderToShot->SetFlying(true);
		gameLayer->addChild(colliderToShot);
		sling->Reset();
	}

	//move flying Colliders.
	for (auto& collider : colliders)
	{
		if (collider->IsFlying())
		{
			collider->Act();
			CheckCollide(collider, targets);
		}
		if (collider->IsBullet())
		{
			if (((Bullet*)collider)->IsExplosing())
			{
				Explosion* explosion = ((Bullet*)collider)->GetExplosion();
				Size size = Director::getInstance()->getVisibleSize();
				Point half = Point(size.width, size.height)/2;
				Point pos = collider->getPosition()-half;
				explosion->setPosition(pos);
				colliderManager->AddExplosion(explosion);
				gameLayer->addChild(explosion);
				((Bullet*)collider)->SetExplosing(false);
			}
		}
	} 
}

void GameManager::CheckCollide(Collider* collider, Vector<Target*> targets){
	for (auto& target : targets)
	{
		if (collider->getBoundingBox().intersectsRect(target->getBoundingBox()))
			target->ApplyEffectToBullet((Bullet*)collider);
	}
}