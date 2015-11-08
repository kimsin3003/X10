#pragma once
#include "Sling.h"
#include "BulletManager.h"
#include "GameLayer.h"
#include "TargetManager.h"

class GameManager
{
public:
	static GameManager* GetInstance();
	void InitTargets(GameLayer* gameLayer);
	void Play(GameLayer* gameLayer);

private:
	void CheckCollide(Bullet* bullet, vector<Target*> targets);
	static GameManager* instance;
	Sling* sling;
	BulletManager* bulletManager;
	TargetManager* targetManager;
	GameManager();
	~GameManager();

};
