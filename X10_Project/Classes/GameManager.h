#pragma once
#include "stdafx.h"
class GameLayer;
class UILayer;
class StageInformation;
class ColliderManager;
class TargetManager;
class Collider;
class Target;
class Sling;

class GameManager
{
public:
	static GameManager* GetInstance();
	static void Reset();
	void InitTargets(GameLayer* gameLayer);
	void Play(GameLayer* gameLayer, UILayer* uiLayer);
	void SetStageNumber(int StageNumber);

private:
	GameManager();
	~GameManager();
	void CheckCollide(Collider* bullet, Vector<Target*> targets);
	void SetStageInformation(const char* FILENAME, int StageNumber);
	//# 복사로 벡터를 통째로 넘기지 마라.. const &로 넘길 것..

private:
	int StageNumber;
	StageInformation* stage;
	static GameManager* instance;
	Sling* sling;
	ColliderManager* colliderManager;
	TargetManager* targetManager;
};
