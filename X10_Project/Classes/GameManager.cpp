#include "stdafx.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "GameManager.h"
#include "StageInformation.h"
#include "ColliderManager.h"
#include "TargetManager.h"
#include "Collider.h"
#include "Bullet.h"
#include "CrossBullet.h"
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

GameManager::~GameManager() {}

void GameManager::SetStage(GameLayer* gameLayer, int StageNumber)
{	
	if (m_stage != nullptr)
	{
		delete m_stage;
	}

	m_stage = new StageInformation(StageNumber);
	m_targetManager->InitTargets(m_stage);
	AppendTargetsToLayer(gameLayer);
	m_colliderManager->InitBullets(m_stage);
	m_sling = SetSling(gameLayer);
}

Sling* GameManager::SetSling(GameLayer* gameLayer)
{
	Sling* sling = Sling::create();
	gameLayer->addChild(sling);
	sling->LoadBullet();
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
	Bullet* bullet = static_cast<Bullet*>(m_colliderManager->GetBulletToShot(sling));
	
	Scene* currentScene = Director::getInstance()->getRunningScene();
	Scene* gameScene = static_cast<Scene*>(currentScene->getChildByName("GameScene"));
	Layer* gameLayer = static_cast<Layer*>(gameScene->getChildByName("GameLayer"));
	gameLayer->addChild(bullet);

	sling->ShotComplete();

	if (m_colliderManager->HasBulletToShot())
	{
		sling->LoadBullet();
	}
}

void GameManager::Play(GameLayer* gameLayer, UILayer* uiLayer)
{
	//벡터를 통째로 복사해서 임시 변수에 담지 말것. 성능 저하의 원인
	Vector<Collider*> colliders = m_colliderManager->GetColliders();
	Vector<Target*> targets = m_targetManager->GetTargets(); 

	for (Collider* collider : colliders)
	{
		if (collider->IsFlying())
		{
			collider->Act();
			CheckCollide(collider, targets);
		}

		if (collider->IsBullet())
		{
			if (((Bullet*)collider)->ShouldExplode())
			{
				Explosion* explosion = (static_cast<Bullet*>(collider))->GetExplosion();
				m_colliderManager->AddExplosion(explosion);
				gameLayer->addChild(explosion);
			}
		}
	}

	m_colliderManager->EraseDeadColliders();
}

void GameManager::CheckCollide(Collider* bullet, Vector<Target*>& targets)
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