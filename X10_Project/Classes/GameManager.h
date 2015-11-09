#pragma once
#include "stdafx.h"
class Sling;
class GameLayer;
class UILayer;
class ColliderManager;
class TargetManager;
class Collider;
class Target;

class GameManager
{
public:
	static GameManager* GetInstance();
	static void Reset();

	void InitTargets(GameLayer* gameLayer);
	void Play(GameLayer* gameLayer, UILayer* uiLayer);

private:
	void CheckCollide(Collider* bullet, Vector<Target*> targets);
	static GameManager* instance;
	Sling* sling;
	ColliderManager* colliderManager;
	TargetManager* targetManager;
	GameManager();
	~GameManager();

};
