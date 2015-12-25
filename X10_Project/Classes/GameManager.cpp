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
//etc
#include <SimpleAudioEngine.h>

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
	m_lastTarget = nullptr;
}

void GameManager::Reset()
{
	m_sling = nullptr;
	delete m_colliderManager;
	m_colliderManager = new ColliderManager();
	delete m_targetManager;
	m_targetManager = new TargetManager();
	m_isJudged = false;
	m_lastTarget = nullptr;
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
	m_curStageNum = stageNum;
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
		m_bulletNumUI.pushBack(bulletSpr);
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

		m_bulletNumUI.back()->removeFromParent();
		m_bulletNumUI.popBack();

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("res/sound_effects/firework_flying2.mp3", false, 1.0f, 0, 0);
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
	m_lastTarget = nullptr; // 한번 충돌한 타겟에 대해 충돌 중 영역을 벗어날 때까지 여러번 충돌체크가 되지 않도록 함.
	bool collidingCheck = false; //현재 충돌중인 타겟이 있는지 체크. --> lastTarget을 유지할 필요가 있는지체크
	for (Target* target : targets)
	{
		if (target == m_lastTarget)
		{
			break;
			collidingCheck = true; // <-????
		}

		if (target->IsEnemy())
		{
			m_targetManager->SaveEnemyPosition(target->getPosition());
		}

		if (collider->IsBullet())
		{

			if (IsCollision(target, collider))
			{
				m_lastTarget = target;
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
				target->ApplyCollisionEffect(explosion);
			}
		}
	}

	if (!collidingCheck)
	{
		m_lastTarget = nullptr;
	}
}

void GameManager::WinProgress(UILayer* uiLayer)
{
	int lastStage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);

	StageScene::m_hasCharacterMoved = false;

	if (m_curStageNum == 0)
	{
		Director::getInstance()->popScene();
	}
	else
	{
		uiLayer->MakeSuccessWidget(m_curStageNum);
	}

	if (lastStage == m_curStageNum && m_curStageNum + 1 <= StageInformation::GetMaxStageNum())
	{
		UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, m_curStageNum + 1);
	}
}

void GameManager::FailProgress(UILayer* uiLayer)
{
	if (m_curStageNum == 0)
	{
		Director::getInstance()->popScene();
	}
	else
	{
		uiLayer->MakeFailWidget(m_curStageNum);
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
			m_sling->RemoveDots();
			WinProgress(uiLayer);
		}
		else if (!m_colliderManager->HasCollider()){
			m_isJudged = true;
			m_sling->ShotComplete();
			m_sling->RemoveDots();
			FailProgress(uiLayer);
		}
	}
}

bool GameManager::IsCollision(Target* target, Collider* collider)
{
	
	float rotation = target->getRotation();
	const Rect colliderBoundingBox = static_cast<Bullet*>(collider)->GetBoundingArea();
	const Rect targetBoundingBox = target->GetBoundingArea();

	if (rotation< 3 && rotation > -3 
		|| rotation< 93 && rotation > 87 
		|| rotation< 183 && rotation > 177 
		|| rotation< 273 && rotation > 267){ //회전이 거의 없는 경우
		//예전 사각형 충돌 판정	
		if (targetBoundingBox.intersectsRect(colliderBoundingBox))
			return true;

		return false;
	}

	float colliderX = collider->getPosition().x;
	float colliderY = collider->getPosition().y;

	float minX = targetBoundingBox.getMinX(); // left margin
	float maxX = targetBoundingBox.getMaxX(); // right margin
	float minY = targetBoundingBox.getMinY(); // lower margin
	float maxY = targetBoundingBox.getMaxY(); // upper margin
	Point LL(minX, minY);
	Point LU(minX, maxY);
	Point RL(maxX, minY);
	Point RU(maxX, maxY);

	//회전사각형만들기
	LL.rotate(target->getPosition(), -CC_DEGREES_TO_RADIANS(target->getRotation()));
	LU.rotate(target->getPosition(), -CC_DEGREES_TO_RADIANS(target->getRotation()));
	RL.rotate(target->getPosition(), -CC_DEGREES_TO_RADIANS(target->getRotation()));
	RU.rotate(target->getPosition(), -CC_DEGREES_TO_RADIANS(target->getRotation()));
	
	// y = Ax + upperB
	// y = Ax + lowerB
	// y = -1/Ax + leftB
	// y = -1/Ax + rightB
	float a = (RU.y- LU.y) / (RU.x - LU.x); //기울기
	
	// RU.y = a * RU.x + upperB
	float upperB = RU.y - a * (RU.x);
	float lowerB = LL.y - a * (LL.x);
	
	// LL.y = (-1/a) * LL.x + leftB
	float leftB = LL.y - (-1 / a) * LL.x;
	float rightB = RU.y - (-1 / a) * RU.x;

	// 네개의 수식 안에 있는지 체크.
	// uppermargin 과 lowermargin 사이에 있는 X, Y 라면 (y-uppermargin) *(y-lowermargin) < 0 이 나옴
	// left 와 right 도 마찬가지.
	
	//디버그용 dot
	//makeDebugPoint(Point(colliderX, (colliderX * a + upperB)), target->getParent());
	//makeDebugPoint(Point(colliderX, (colliderX * a + lowerB)), target->getParent());
	//makeDebugPoint(Point(colliderX, (colliderX * (-1 / a) + rightB)), target->getParent());
	//makeDebugPoint(Point(colliderX, (colliderX * (-1 / a) + leftB)), target->getParent());

	if (
		((colliderX * a + upperB) - colliderY) * ((colliderX * a + lowerB) - colliderY) < 0
		&&
		((colliderX * (-1 / a) + leftB) - colliderY) * ((colliderX * (-1 / a) + rightB) - colliderY) < 0
		)
	{
		return true;
	}
	else 
		return false;
	
}

void GameManager::makeDebugPoint(Point p, Node* spr)
{
	Sprite* dot = Sprite::create(FileStuff::DEBRIS);
	dot->setScale(2.);
	spr->addChild(dot);
	Point pos = spr->convertToWorldSpace(Point::ZERO);
	dot->setPosition(p -  pos);

	Sequence* action = Sequence::create(DelayTime::create(0.1), RemoveSelf::create(),NULL);
	dot->runAction(action);
}