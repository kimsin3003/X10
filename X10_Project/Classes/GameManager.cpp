#include "stdafx.h"
#include "GameManager.h"
#include "FileStuff.h"
#include "ConstVars.h"
//���̾�
#include "GameLayer.h"
#include "UILayer.h"
//��������
#include "StageInformation.h"
#include "StageScene.h"
#include "GameScene.h"
//�Ŵ���
#include "ColliderManager.h"
#include "TargetManager.h"
//�ö��̴�
#include "Collider.h"
#include "Bullet.h"
#include "Explosion.h"
//Ÿ��
#include "Target.h"
#include "Mirror.h"
#include "Virtical_Mirror.h"

//����
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

GameManager::GameManager() : m_sling(nullptr), m_isJudged(false), m_curStageNum(0)
{
	m_colliderManager = new ColliderManager();
	m_targetManager = new TargetManager();
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
		GameLayer* m_gameLayer = gameScene->GetGameLayer();

		m_gameLayer->addChild(bullet);

		m_bulletNumUI.back()->removeFromParent();
		m_bulletNumUI.popBack();

		if (m_curStageNum == 12)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileStuff::SOUND_CAR_BREAK, false, 1.0f, 0, 0);
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileStuff::SOUND_FIREWORK_FLYING, false, 1.0f, 0, 0);
		}

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
				if (m_curStageNum == 12)
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileStuff::SOUND_CAR_CRASH, false, 1.0f, 0, 0);
				}
				else 
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileStuff::SOUND_FIREWORK_EXPLOSION, false, 1.0f, 0, 0);
				}
			}
		}
	}

	m_colliderManager->EraseDeadColliders();
	m_targetManager->EraseDeadTargets();
	ControlWinFailProgress(uiLayer);
}

void GameManager::CheckCollide(Collider* collider, Vector<Target*>& targets)
{
	Target* currentCollidingTarget;
	currentCollidingTarget = nullptr; // �ѹ� �浹�� Ÿ�ٿ� ���� �浹 �� ������ ��� ������ ������ �浹üũ�� ���� �ʵ��� ��.
	//�� �ּ��� ������ Ʋ��... �̰��� �� �ݶ��̴��� ���ؼ� �� �����ӳ��� �����浹�� �ִ��� �˻��ϴ� �ڵ���.

	bool collidingCheck = false; //���� �浹���� Ÿ���� �ִ��� üũ. --> lastTarget�� ������ �ʿ䰡 �ִ���üũ
	for (Target* target : targets)
	{
		//if (target == currentCollidingTarget)
		//{
		//	collidingCheck = true;
		//	break;
		//}

		if (collider->IsBullet())
		{
			if (IsCollision(target, collider))
			{
				Bullet* bullet = static_cast<Bullet*>(collider);
				if (bullet->m_currentCollidingTarget == target)
				{
					collidingCheck = true;
					continue;
				}

				currentCollidingTarget = target;
				target->ApplyCollisionEffect(collider);
				
				if (target->IsEnemy())
				{
					if (m_curStageNum >= 9)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
							FileStuff::SOUND_UFO_EXPLODE_GIRL, false, 1.0f, 0, 0);
					}
					else
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
							FileStuff::SOUND_UFO_EXPLODE_DEFAULT, false, 1.0f, 0, 0);
					}
				}

				collidingCheck = true;
				bullet->m_currentCollidingTarget = target;

				if (target->IsMirror())
				{
					break;
				}
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
				if (target->IsEnemy())
				{
					if (m_curStageNum >= 9)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
							FileStuff::SOUND_UFO_EXPLODE_GIRL, false, 1.0f, 0, 0);
					}
					else
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
							FileStuff::SOUND_UFO_EXPLODE_DEFAULT, false, 1.0f, 0, 0);
					}
				}

				target->ApplyCollisionEffect(explosion);
			}
		}
	}

	if (!collidingCheck)
	{
		currentCollidingTarget = nullptr;
		Bullet* bullet = dynamic_cast<Bullet*>(collider);
		if (bullet != nullptr)
		{
			bullet->m_currentCollidingTarget = nullptr;
		}
	}
}

void GameManager::WinProgress(UILayer* uiLayer)
{
	int lastStage = UserDefault::getInstance()->getIntegerForKey(ConstVars::LASTSTAGE);

	if (m_curStageNum == 0)
	{
		Director::getInstance()->popScene();
	}
	else
	{
		if (lastStage == m_curStageNum && m_curStageNum + 1 <= StageInformation::GetMaxStageNum())
		{
			UserDefault::getInstance()->setIntegerForKey(ConstVars::LASTSTAGE, m_curStageNum + 1);
		}

		uiLayer->MakeSuccessWidget(m_curStageNum);
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
		else if (!m_colliderManager->HasCollider())
		{
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
		|| rotation < 93 && rotation > 87
		|| rotation < 183 && rotation > 177
		|| rotation < 273 && rotation > 267){ //ȸ���� ���� ���� ���
		//���� �簢�� �浹 ����	
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

	//ȸ���簢�������
	LL.rotate(target->getPosition(), -CC_DEGREES_TO_RADIANS(target->getRotation()));
	LU.rotate(target->getPosition(), -CC_DEGREES_TO_RADIANS(target->getRotation()));
	RL.rotate(target->getPosition(), -CC_DEGREES_TO_RADIANS(target->getRotation()));
	RU.rotate(target->getPosition(), -CC_DEGREES_TO_RADIANS(target->getRotation()));

	// y = Ax + upperB
	// y = Ax + lowerB
	// y = -1/Ax + leftB
	// y = -1/Ax + rightB
	float a = (RU.y - LU.y) / (RU.x - LU.x); //����

	// RU.y = a * RU.x + upperB
	float upperB = RU.y - a * (RU.x);
	float lowerB = LL.y - a * (LL.x);

	// LL.y = (-1/a) * LL.x + leftB
	float leftB = LL.y - (-1 / a) * LL.x;
	float rightB = RU.y - (-1 / a) * RU.x;

	if (
		((colliderX * a + upperB) - colliderY) * ((colliderX * a + lowerB) - colliderY) < 0
		&&
		((colliderX * (-1 / a) + leftB) - colliderY) * ((colliderX * (-1 / a) + rightB) - colliderY) < 0
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameManager::makeDebugPoint(Point p, Node* spr)
{
	Sprite* dot = Sprite::create(FileStuff::DEBRIS);
	dot->setScale(2.);
	spr->addChild(dot);
	Point pos = spr->convertToWorldSpace(Point::ZERO);
	dot->setPosition(p -  pos);

	Sequence* action = Sequence::create(DelayTime::create(0.1f), RemoveSelf::create(),NULL);
	dot->runAction(action);
}