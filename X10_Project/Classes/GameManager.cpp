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
#include "Explosion.h"
#include "CrossExplosion.h"

GameManager* GameManager::m_instance = nullptr;

GameManager* GameManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new GameManager();
	}
	return m_instance;
}

GameManager::GameManager()
{
	m_sling = nullptr;
	m_colliderManager = new ColliderManager();
	m_targetManager = new TargetManager();
	m_stage = nullptr;
}

GameManager::~GameManager()
{

}

void GameManager::SetStage(GameLayer* gameLayer, int StageNumber)
{	
	if (m_stage != nullptr)
	{
		delete m_stage;
	}

	m_stage = new StageInformation(StageNumber);
	
	//해당 스테이지의 타깃 정보를 벡터에 저장
	m_targetManager->InitTargets(m_stage);
	//레이어에 붙여준다
	AppendTargetsToLayer(gameLayer);
	
	//불렛 세팅
	m_colliderManager->InitBullets(m_stage);

	//슬링 세팅
	m_sling = SetSling(gameLayer);
}

Sling* GameManager::SetSling(GameLayer* gameLayer)
{

	Sling* sling = Sling::create();
	gameLayer->addChild(sling);

	//총알이 있으면
	if (m_colliderManager->HasBulletToShot())
	{
		//슬링에게 총알을 장전하라고 알린다.
		sling->LoadBullet();
	}

	return sling;
}

void GameManager::AppendTargetsToLayer(GameLayer* gameLayer)
{
	Vector<Target*> targets = m_targetManager->GetTargets();

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
		Bullet* bullet = static_cast<Bullet*>(m_colliderManager->GetBulletToShot(sling));
		Scene* currentScene = Director::getInstance()->getRunningScene();
		Scene* gameScene = static_cast<Scene*>(currentScene->getChildByName("GameScene"));
		Layer* gameLayer = static_cast<Layer*>(gameScene->getChildByName("GameLayer"));
		gameLayer->addChild(bullet);
		//슬링에게 발사가 완료되었다고 알린다.
		sling->ShotComplete();
		
		//총알이 있으면
		if (m_colliderManager->HasBulletToShot())
		{
			//슬링에게 총알을 장전하라고 알린다.
			sling->LoadBullet();
		}
	}
}

void GameManager::Play(GameLayer* gameLayer, UILayer* uiLayer)
{
	//벡터를 통째로 복사해서 임시 변수에 담지 말것. 성능 저하의 원인
	Vector<Collider*> colliders = m_colliderManager->GetColliders();
	Vector<Target*> targets = m_targetManager->GetTargets(); 


	for (Collider* collider : colliders)
	{
		//1. 날고 있는 'collider'는 
		if (collider->IsFlying())
		{
			//'Act()'를 시키고
			collider->Act(m_colliderManager);
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
				m_colliderManager->AddExplosion(explosion);
				gameLayer->addChild(explosion);
			}
		}
	}
	m_colliderManager->EraseDeadColliders();
}

void GameManager::CheckCollide(Collider* bullet, const Vector<Target*>& targets)
{

	static Target* m_lastTarget = nullptr;
	for (Target* target : targets)
	{
		if (target == m_lastTarget)
			continue;

		if (bullet->IsBullet())
		{
			const Rect colliderBoundingBox = (static_cast<Bullet*>(bullet))->GetBoundingArea();
			const Rect targetBoundingBox = target->GetBoundingArea();

			if (colliderBoundingBox.intersectsRect(targetBoundingBox))
			{
				m_lastTarget = target;
				target->ApplyCollisionEffect(bullet);
			}
			else{
				if (m_lastTarget == target)
					m_lastTarget = nullptr;
			}
		}
		else
		{
			const float explosionRadius = (static_cast<Explosion*>(bullet))->GetBoundingRadius();
			const Vec2 explosionPosition = (static_cast<Explosion*>(bullet))->getPosition();
			const Rect targetBoundingBox = target->GetBoundingArea();

			if (targetBoundingBox.intersectsCircle(explosionPosition, explosionRadius))
			{
				m_lastTarget = target;
				target->ApplyCollisionEffect(bullet);
			}
		}
	}
}