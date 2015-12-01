#include "stdafx.h"
#include "GameManager.h"
#include "FileStuff.h"
#include "ConstVars.h"
//레이어
#include "GameLayer.h"
#include "UILayer.h"
//스테이지
#include "StageInformation.h"
#include "StageScene.h"
#include "GameScene.h"
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
	m_isJudged = false;
}


void GameManager::Reset()
{
	m_sling = nullptr;
	delete m_colliderManager;
	m_colliderManager = new ColliderManager();
	delete m_targetManager;
	m_targetManager = new TargetManager();
	m_isJudged = false;
}


GameManager::~GameManager() {}

void GameManager::SetStage(GameLayer* gameLayer, int stageNumber)
{	
	Reset();
	StageInformation stageInfo(stageNumber);
	m_targetManager->InitTargets(&stageInfo);
	AppendTargetsToLayer(gameLayer);
	m_colliderManager->InitBullets(&stageInfo);
	m_sling = SetSling(gameLayer);
	m_stage = stageNumber;
	m_isJudged = false;
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
	Vector<Target*> targets = m_targetManager->GetTargets(); ///# 벡터 복사 금지 성능 저하됨

	for (Target* target : targets)
	{
		gameLayer->addChild(target);
	}
}

void GameManager::ShotBullet(Sling* sling)
{
	Bullet* bullet = static_cast<Bullet*>(m_colliderManager->GetBulletToShot(sling)); ///# 여기에서 casting이 왜 필요?
	
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
	Vector<Collider*>& colliders = m_colliderManager->m_colliders;
	Vector<Target*>& targets = m_targetManager->m_targets;
	Collider* collider = nullptr;
	for (int i = 0; i < colliders.size(); i++)
	{
		collider = colliders.at(i);
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
	m_targetManager->EraseDeadTargets();

	if (!m_isJudged)
	{
		if (!m_targetManager->HasEnemy())
		{
			m_isJudged = true;
			m_sling->ShotComplete();
			m_sling->removeAllChildren();
			WinProgress(uiLayer);
		}
		else if (!m_colliderManager->HasCollider()){
			m_isJudged = true;
			m_sling->ShotComplete();
			m_sling->removeAllChildren();
			FailProgress(uiLayer);
		}
	}
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
		else if ( Explosion* explosion = dynamic_cast<Explosion*>(bullet))
		{
			const float explosionRadius = explosion->GetBoundingRadius();
			const Vec2 explosionPosition = explosion->getPosition();
			const Rect targetBoundingBox = target->GetBoundingArea();

			if ( targetBoundingBox.intersectsCircle( explosionPosition, explosionRadius) )
			{
				m_lastTarget = target;
				target->ApplyCollisionEffect(explosion);
			}
		}
	}
}

void GameManager::WinProgress(UILayer* uiLayer)
{
	int lastStage = UserDefault::getInstance()->getIntegerForKey(ConstVars::lastStage);
	if (lastStage < m_stage + 1 && m_stage + 1 <= StageInformation::GetMaxStageNum())
	{
		UserDefault::getInstance()->setIntegerForKey(ConstVars::lastStage, m_stage + 1);
	}
	uiLayer->MakeSuccessWidget(m_stage);
}

void GameManager::FailProgress(UILayer* uiLayer)
{
	uiLayer->MakeFailWidget(m_stage);
}
