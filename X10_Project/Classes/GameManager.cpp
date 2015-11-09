#include "stdafx.h"
#pragma once
#include "GameManager.h"
#include "Bullet.h"
#include "Target.h"
GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	sling = Sling::GetInstance();
	bulletManager = BulletManager::GetInstance();
	targetManager = TargetManager::GetInstance();
}

GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::InitTargets(GameLayer* gameLayer){
	
	Vector<Target*> targets = targetManager->GetTargets();
	for (auto iter = targets.begin(); iter < targets.end(); iter++)
		gameLayer->addChild(*iter);
}

//main game logic
void GameManager::Play(GameLayer* gameLayer)
{
	Vector<Bullet*> bullets = bulletManager->GetBullets();
	Vector<Target*> targets = targetManager->GetTargets(); 
	//shot if sling shotted the bullet. --> isShotted가 언제 어떻게 바뀌냐에 따라 여기는 바뀌어야할듯.

	
	if (bulletManager->HasNextBullet()){
		sling->NewBulletLoad();
	}

	if (sling->IsShotted()){
		Bullet* bulletToShot = bulletManager->GetBulletToShot();
		bulletToShot->SetDirection(sling->GetDirection());
		bulletToShot->SetSpeed(1);
		bulletToShot->SetFlying(true);
		gameLayer->addChild(bulletToShot);
		sling->Reset();
	}

	//move flying bullets.
	for (auto& bullet : bullets){
		if (bullet->IsFlying()){
			bullet->Move();
			CheckCollide(bullet, targets);
		}
	} 

}

void GameManager::CheckCollide(Bullet* bullet, Vector<Target*> targets){
	for (auto& target : targets){
		if (bullet->getBoundingBox().intersectsRect(target->getBoundingBox()))
			target->SetEffect(bullet);
	}
}

