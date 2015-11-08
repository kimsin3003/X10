#include "stdafx.h"
#include "GameManager.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Sling.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	sling = Sling::GetInstance();
	bulletManager = BulletManager::GetInstance();
}

GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::Play()
{
	vector<Bullet*> bullets = BulletManager::GetInstance()->GetBullets();
	
	if (sling->IsShoted()){
		Bullet* bulletToShot = bulletManager->GetBulletToShot();
		bulletToShot->SetDirection(sling->GetDirection());
		bulletToShot->SetSpeed(sling->GetSpeed());

	}


	for (auto& bullet : bullets){
		if (bullet->IsFlying()){
			bullet->Move();
		}
	}
}

