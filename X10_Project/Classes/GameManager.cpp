#include "stdafx.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "GameManager.h"
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
	colliderManager = ColliderManager::GetInstance();
	targetManager = TargetManager::GetInstance();
}

GameManager::~GameManager(){}

void GameManager::Reset()
{
	delete instance;
	instance = nullptr;
	ColliderManager::GetInstance()->Reset();
//	TargetManager::GetInstance()->Reset();
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
		Bullet* bullet = (Bullet*)colliderManager->GetBulletToShot();
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
			collider->Act();
			//그 'collider'이 타깃들과 충돌하는지 체크한다. 
			CheckCollide(collider, targets);
		}

		//그 'collider'가 bullet이면
		if (collider->IsBullet())
		{
			//그리고 폭발하는 중이면
			if (((Bullet*)collider)->IsExplosing()) ///# C++ 캐스팅을 써라.
			{
				//폭발시켜주고
				Explosion* explosion = ((Bullet*)collider)->GetExplosion();
				gameLayer->addChild(explosion);
				//그 'collider'(bullet)에게 상태를 바꾸라고 알린다
				((Bullet*)collider)->StopExplosing();
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