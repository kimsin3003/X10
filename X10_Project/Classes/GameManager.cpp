#include "stdafx.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "GameManager.h"
#include "StageInformation.h"
#include "ColliderManager.h"
#include "TargetManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "Target.h"
#include "Sling.h"
#include "Mirror.h"

GameManager* GameManager::instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

GameManager::GameManager()
{
	sling = nullptr;
	colliderManager = new ColliderManager();
	targetManager = new TargetManager();
	stage = nullptr;
}

GameManager::~GameManager()
{

}

void GameManager::Reset()
{
	delete instance;
	instance = nullptr;
}

void GameManager::SetStage(GameLayer* gameLayer, int StageNumber)
{	
	if (stage != nullptr)
	{
		delete stage;
	}

	stage = new StageInformation(StageNumber);
	
	//해당 스테이지의 타깃 정보를 벡터에 저장
	targetManager->InitTargets(stage);
	//레이어에 붙여준다
	AppendTargetsToLayer(gameLayer);
	
	//불렛 세팅
	colliderManager->InitBullets(stage);

	//슬링 세팅
	sling = SetSling(gameLayer);
}

Sling* GameManager::SetSling(GameLayer* gameLayer)
{

	Sling* sling = Sling::create();
	gameLayer->addChild(sling);

	//총알이 있으면
	if (colliderManager->HasBullet())
	{
		//슬링에게 총알을 장전하라고 알린다.
		sling->LoadBullet();
	}

	return sling;
}

void GameManager::AppendTargetsToLayer(GameLayer* gameLayer)
{
	Vector<Target*> targets = targetManager->GetTargets();

	for (Target* target : targets)
	{
		gameLayer->addChild(target);
	}

}

void GameManager::ShotBullet(Sling* sling)
{
	//슬링의 상태가 'IsShotted'이면
	if (sling->IsShotted())
	{
		//위치, 각도, 속도가 세팅된 bullet을 생성하고 레이어에 붙인다
		Bullet* bullet = static_cast<Bullet*>(colliderManager->GetBulletToShot(sling));
		Scene* currentScene = Director::getInstance()->getRunningScene();
		Scene* gameScene = static_cast<Scene*>(currentScene->getChildByName("GameScene"));
		Layer* gameLayer = static_cast<Layer*>(gameScene->getChildByName("GameLayer"));
		gameLayer->addChild(bullet);
		//슬링에게 발사가 완료되었다고 알린다.
		sling->ShotComplete();
		
		//총알이 있으면
		if (colliderManager->HasBullet())
		{
			//슬링에게 총알을 장전하라고 알린다.
			sling->LoadBullet();
		}
	}
}

void GameManager::Play(GameLayer* gameLayer, UILayer* uiLayer)
{
	//벡터를 통째로 복사해서 임시 변수에 담지 말것. 성능 저하의 원인
	Vector<Collider*> colliders = colliderManager->GetColliders();
	Vector<Target*> targets = targetManager->GetTargets(); 


	for (Collider* collider : colliders)
	{
		//1. 날고 있는 'collider'는 
		if (collider->IsFlying())
		{
			//'Act()'를 시키고
			collider->Act(colliderManager);
			//그 'collider'가 타깃들과 충돌하는지 체크한다. 
			CheckCollide(collider, targets);
		}

		//2. 'collider'가 bullet이고
		if (collider->IsBullet())
		{
			//폭발해야하면
			if (((Bullet*)collider)->ShouldExplode())
			{
				//폭발을 생성하여 벡터에 넣고 레이어에 붙여준다
				Explosion* explosion = (static_cast<Bullet*>(collider))->GetExplosion();
				colliderManager->AddExplosion(explosion);
				gameLayer->addChild(explosion);
			}
		}
	}
}

void GameManager::CheckCollide(Collider* collider, Vector<Target*> targets)
{
	static Target* lastTarget = nullptr;
	for (Target*& target : targets)
	{
		if (target == lastTarget)
			continue;

		if (collider->IsBullet())
		{
			const Rect colliderBoundingBox = (static_cast<Bullet*>(collider))->GetBoundingArea();
			const Rect targetBoundingBox = target->GetBoundingArea();

			if (colliderBoundingBox.intersectsRect(targetBoundingBox))
			{
				lastTarget = target;
				target->ApplyCollisionEffect(collider);
			}
		}
		else
		{
			const float explosionRadius = (static_cast<Explosion*>(collider))->GetBoundingRadius();
			const Vec2 explosionPosition = (static_cast<Explosion*>(collider))->getPosition();
			const Rect targetBoundingBox = target->GetBoundingArea();

			if (targetBoundingBox.intersectsCircle(explosionPosition, explosionRadius))
			{
				lastTarget = target;
				target->ApplyCollisionEffect(collider);
			}
		}
	}
}