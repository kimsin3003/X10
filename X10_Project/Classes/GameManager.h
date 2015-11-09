#pragma once
#include "Sling.h"
#include "ColliderManager.h"
#include "GameLayer.h"
#include "TargetManager.h"

class GameManager
{
public:
	static GameManager* GetInstance();
	void InitTargets(GameLayer* gameLayer);
	void Play(GameLayer* gameLayer);

private:
	void CheckCollide(Collider* bullet, Vector<Target*> targets);
	static GameManager* instance;
	Sling* sling;
	ColliderManager* colliderManager;
	TargetManager* targetManager;
	GameManager();
	~GameManager();

};
