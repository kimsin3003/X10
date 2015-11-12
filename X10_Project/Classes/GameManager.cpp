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
	sling = Sling::GetInstance();
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

void GameManager::SetStageInformation(int StageNumber)
{	
	if (stage != nullptr)
	{
		delete stage;
	}

	stage = new StageInformation(StageNumber);
	
//	targetManager->InitTargets(stage);
	colliderManager->InitBullets(stage);
}


void GameManager::InitTargets(GameLayer* gameLayer)
{
	Vector<Target*> targets = targetManager->GetTargets();
	for (Target* target : targets)
	{
		gameLayer->addChild(target);
	}
}

void GameManager::Play(GameLayer* gameLayer, UILayer* uiLayer)
{
	//벡터를 통째로 복사해서 임시 변수에 담지 말것. 성능 저하의 원인
	Vector<Collider*> colliders = colliderManager->GetColliders();
	Vector<Target*> targets = targetManager->GetTargets(); 

	//총알이 있으면
	if (colliderManager->HasBullet())
	{
		//슬링에게 총알을 장전하라고 알린다.
		sling->LoadBullet();
	}

	//슬링의 상태가 'IsShotted'이면
	if (sling->IsShotted())
	{
		//위치, 각도, 속도가 세팅된 bullet을 생성하여 레이어에 붙인다
		Bullet* bullet = (Bullet*)colliderManager->GetBulletToShot(sling);
		gameLayer->addChild(bullet);
		//슬링에게 발사가 완료되었다고 알린다.
		sling->ShotComplete();
	}

	for (Collider* collider : colliders)
	{
		//날고 있는 'collider'는 
		if (collider->IsFlying())
		{
			//'Act()'를 하라고 시키고
			collider->Act(colliderManager);
			//그 'collider'가 타깃들과 충돌하는지 체크한다. 
			CheckCollide(collider, targets);
		}

		//그 'collider'가 bullet이고
		if (collider->IsBullet())
		{
			//폭발해야하면
			if (((Bullet*)collider)->IsExplosing()) ///# C++ 캐스팅을 써라.
			{
				//폭발 넣어주고 붙여준다
				Explosion* explosion = ((Bullet*)collider)->GetExplosion();
				colliderManager->AddExplosion(explosion);
				gameLayer->addChild(explosion);
			}
		}
	} 
}

void GameManager::CheckCollide(Collider* collider, Vector<Target*> targets)
{
	for (Target* target : targets)
	{
		if (collider->getBoundingBox().intersectsRect(target->getBoundingBox()))
		{
			target->ApplyEffectToBullet((Bullet*)collider);
		}
	}
}