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
		///# auto쓰는데 왜 iter++ ?? 이번 프로젝트는 최대한 auto를 쓰지 말기를 추천한다. 
		///#타입 추론 및 이터래이터의 타입을 정확히 알고 쓰는 연습을 하기 위함.
		gameLayer->addChild(*iter);
}

//main game logic
void GameManager::Play(GameLayer* gameLayer, UILayer* uiLayer)
{
	Vector<Collider*> colliders = colliderManager->GetColliders(); 
	///# 벡터를 통째로 복사해서 임시 변수에 담지 말것... 성능 저하의 원인
	Vector<Target*> targets = targetManager->GetTargets(); 
	//shot if sling shotted the Collider. --> isShotted가 언제 어떻게 바뀌냐에 따라 여기는 바뀌어야할듯.

	if (colliderManager->HasNextCollider())
	{
		sling->NewColliderLoad();
	}

	if (sling->IsShotted())
	{
		Bullet* colliderToShot = (Bullet*)colliderManager->GetColliderToShot();
		colliderToShot->setPosition(sling->getPosition());
		colliderToShot->setRotation(sling->GetRotationAngle());
		colliderToShot->SetDirection(sling->GetDirection());
		colliderToShot->SetSpeed(sling->GetSpeed()/20);
		colliderToShot->SetFlying(true);
		gameLayer->addChild(colliderToShot);
		sling->Reset();
	}

	Collider* collider;
	for (int i = 0; i < colliders.size(); i++)
	{
		collider = colliders.at(i);
		if (collider->IsFlying())
		{
			collider->Act();
			CheckCollide(collider, targets);
		}

		if (collider->IsBullet())
		{
			if (((Bullet*)collider)->IsExplosing()) ///# C++ 캐스팅을 써라.
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