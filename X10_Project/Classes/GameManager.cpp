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
#include "CollectionManager.h"
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

void GameManager::SetStage(GameLayer* gameLayer, UILayer* uiLayer, int stageNum)
{	
	Reset();
	StageInformation stageInfo(stageNum);
	m_targetManager->InitTargets(&stageInfo);
	AppendTargetsToLayer(gameLayer);
	m_colliderManager->InitBullets(&stageInfo);
	AppendBulletsToLayer(uiLayer);
	m_sling = InitSling(gameLayer);
	m_stage = stageNum;
}

Sling* GameManager::InitSling(GameLayer* gameLayer)
{
	Sling* sling = Sling::create();
	gameLayer->addChild(sling);
	sling->LoadBullet();
	return sling;
}

void GameManager::AppendTargetsToLayer(GameLayer* gameLayer)
{
	for (Target* target : m_targetManager->m_targets)
	{
		gameLayer->addChild(target);
	}
}

void GameManager::AppendBulletsToLayer(UILayer* uiLayer)
{
	for (int i = 0; i < m_colliderManager->m_bulletNum; i++)
	{
		Bullet* bullet = static_cast<Bullet*>(m_colliderManager->m_colliders.at(i));
		Sprite* bulletSpr = bullet->GetSprite();
		uiLayer->addChild(bulletSpr);
		bulletSpr->setPosition(Vec2(45 + i*25, 50));
	}
}

void GameManager::ShotBullet(Sling* sling)
{
	Bullet* bullet = m_colliderManager->GetBulletToShot(sling);
	
	if (bullet)
	{
		Scene* currentScene = Director::getInstance()->getRunningScene();
		GameScene* gameScene = static_cast<GameScene*>(currentScene->getChildByName("GameScene"));
		GameLayer* gameLayer = gameScene->GetGameLayer();
		UILayer* uiLayer = gameScene->GetUILayer();

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

		if (collider->IsBullet())
		{
			Bullet* bullet = static_cast<Bullet*>(collider);
			if (bullet->IsToExplode())
			{
				Explosion* explosion = bullet->GetExplosion();
				m_colliderManager->AddExplosion(explosion);
				gameLayer->addChild(explosion);
			}
		}
	}

	m_colliderManager->EraseDeadColliders();
	m_targetManager->EraseDeadTargets();
	ControlWinFailProgress(uiLayer);
}

void GameManager::CheckCollide(Collider* collider, Vector<Target*>& targets)
{
	static Target* lastTarget = nullptr; // 한번 충돌한 타겟에 대해 충돌 중 영역을 벗어날 때까지 여러번 충돌체크가 되지 않도록 함.
	bool collidingCheck = false; //현재 충돌중인 타겟이 있는지 체크. --> lastTarget을 유지할 필요가 있는지체크
	for (Target* target : targets)
	{
		if (target == lastTarget)
		{
			continue;
		}

		if (target->IsEnemy())
		{
			m_targetManager->SaveEnemyPosition(target->getPosition());
			EnemyDyingEffect();
		}

		if (collider->IsBullet())
		{
			const Rect colliderBoundingBox = static_cast<Bullet*>(collider)->GetBoundingArea();
			const Rect targetBoundingBox = target->GetBoundingArea();

			if (colliderBoundingBox.intersectsRect(targetBoundingBox))
			{
				lastTarget = target;
				target->ApplyCollisionEffect(collider);
				collidingCheck = true;
			}
		}
		else
		{
			Explosion* explosion = static_cast<Explosion*>(collider);
			const float explosionRadius = explosion->GetBoundingRadius();
			const Vec2 explosionPosition = explosion->getPosition();
			const Rect targetBoundingBox = target->GetBoundingArea();

			if ( targetBoundingBox.intersectsCircle( explosionPosition, explosionRadius) )
			{
				lastTarget = target;
				target->ApplyCollisionEffect(explosion);
			}
		}
	}

	if (!collidingCheck)
	{
		lastTarget = nullptr;
	}
}

void GameManager::EnemyDyingEffect()
{
	/*
	ParticleSmoke* enemyDyingEffect = ParticleSmoke::create();
	enemyDyingEffect->setPosition(enemyPos);
	gameLayer->addChild(enemyDyingEffect);
	*/
}

void GameManager::SetCollectionPos(const Vec2& pos)
{
	const Vec2 compensateToParentPos = Vec2(160, 0);
	m_curCollection->setPosition(pos + compensateToParentPos);
}

void GameManager::EarnCollectionEvent(UILayer* uiLayer)
{
	GameScene* gameScene = static_cast<GameScene*>(uiLayer->getParent());
	const Point& enemyPos = m_targetManager->GetEnemyPosition();
	const Vec2& aboveCharacterPos = gameScene->GetCharacterPos() + Vec2(0, 100);

	m_curCollection = m_collectionManager->GetCollectionSprOfStage(m_stage);
	m_curCollection->setPosition(enemyPos);
	uiLayer->addChild(m_curCollection);

	//part 1
	MoveBy* moveBy_00 = MoveBy::create(1.50f, Point(0, -10));
	MoveBy* moveBy_01 = MoveBy::create(1.00f, Point(0, -10));

	Blink* blink_00 = Blink::create(1.50f, 5);
	Blink* blink_01 = Blink::create(1.00f, 5);

	FadeIn* fadeIn_00 = FadeIn::create(1.50f);
	FadeOut* fadeOut_00 = FadeOut::create(1.00f);

	Spawn* spawn_00 = Spawn::create(fadeIn_00, moveBy_00, blink_00, NULL);
	Spawn* spawn_01 = Spawn::create(fadeOut_00, moveBy_01, blink_01, NULL);

	//part 2
	CallFuncN* callFuncN = CallFuncN::create(CC_CALLBACK_0
		(GameManager::SetCollectionPos, this, aboveCharacterPos));

	MoveBy* moveBy_02 = MoveBy::create(1.50f, Point(0, -30));
	MoveBy* moveBy_03 = MoveBy::create(1.00f, Point(0, -20));

	Blink* blink_02 = Blink::create(1.50f, 5);
	Blink* blink_03 = Blink::create(1.00f, 5);

	FadeIn* fadeIn_01 = FadeIn::create(0.01f);
	FadeOut* fadeOut_01 = FadeOut::create(2.50f);

	Spawn* spawn_02 = Spawn::create(fadeIn_01, moveBy_02, blink_02, NULL);
	Spawn* spawn_03 = Spawn::create(fadeOut_01, moveBy_03, blink_03, NULL);

	Sequence* sequence = Sequence::create(
		spawn_00, spawn_01, callFuncN, spawn_02, spawn_03, NULL);

	m_curCollection->runAction(sequence);
}

void GameManager::WinProgress(UILayer* uiLayer)
{
	int lastStage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);

	if (m_stage == lastStage &&
		(m_stage == CollectionManager::SHOES ||
		m_stage == CollectionManager::SCARF ||
		m_stage == CollectionManager::BOTTLE ||
		m_stage == CollectionManager::MONITOR ||
		m_stage == CollectionManager::LETTER))
	{
		EarnCollectionEvent(uiLayer);

		DelayTime* waitEventTime = DelayTime::create(4.50f);
		CallFuncN* showWidget = CallFuncN::create(CC_CALLBACK_0(
			UILayer::MakeSuccessWidget, uiLayer, m_stage));
		Sequence* waitAndshow = Sequence::create(waitEventTime, showWidget, NULL);

		uiLayer->runAction(waitAndshow);
	}
	else
	{
		if (m_stage==0)
		{
			Director::getInstance()->popScene();
		}
		else
		{
			uiLayer->MakeSuccessWidget(m_stage);
		}
	}

	if (lastStage == m_stage && m_stage + 1 <= StageInformation::GetMaxStageNum())
	{
		UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, m_stage + 1);
	}
}

void GameManager::FailProgress(UILayer* uiLayer)
{
	if (m_stage == 0)
	{
		Director::getInstance()->popScene();
	}
	else
	{
		uiLayer->MakeFailWidget(m_stage);
	}
}

void GameManager::ControlWinFailProgress(UILayer* uiLayer)
{
	if (!m_isJudged)
	{
		if (!m_targetManager->HasEnemy())
		{
			m_isJudged = true;
			m_sling->ShotComplete();
			WinProgress(uiLayer);
		}
		else if (!m_colliderManager->HasCollider()){
			m_isJudged = true;
			m_sling->ShotComplete();
			FailProgress(uiLayer);
		}
	}
}
