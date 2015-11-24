#include "stdafx.h"
#include "GameManager.h"
//레이어
#include "GameLayer.h"
#include "UILayer.h"
//스테이지
#include "StageInformation.h"
//매니저
#include "ColliderManager.h"
#include "TargetManager.h"
//컬라이더
#include "Collider.h"
#include "Bullet.h"
#include "CrossBullet.h"
#include "Explosion.h"
//타깃
#include "Target.h"
//슬링
#include "Sling.h"

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
	
	if (bullet)
	{
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
}

void GameManager::Play(GameLayer* gameLayer, UILayer* uiLayer)
{
	///# 왜 임시변수에 복사해서 쓰지? 효율 나빠짐.
	Vector<Collider*> colliders = m_colliderManager->m_colliders;
	Vector<Target*> targets = m_targetManager->m_targets;

	for (Collider* collider : colliders)
	{
		if (collider->IsFlying())
		{
			collider->Act();
			CheckCollide(collider, targets);
		}

		if (Bullet* bullet = dynamic_cast<Bullet*>(collider))
		{
			if (bullet->ShouldExplode())
			{
				Explosion* explosion = bullet->GetExplosion();
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
			const Rect& colliderBoundingBox = (static_cast<Bullet*>(bullet))->GetBoundingArea();
			const Rect& targetBoundingBox = target->GetBoundingArea();

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