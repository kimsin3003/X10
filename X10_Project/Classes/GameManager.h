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

	void Play(GameLayer* gameLayer, UILayer* uiLayer);
	
	void SetStage(GameLayer* gameLayer, int StageNumber);
	void AppendTargetsToLayer(GameLayer* gameLayer);
	Sling* SetSling(GameLayer* gameLayer);

	void ShotBullet(Sling* sling);

private:
	GameManager();
	~GameManager();
	void CheckCollide(Collider* bullet, Vector<Target*> targets); ///# 복사로 벡터를 통째로 넘기지 마라.. const &로 넘길 것..
	

private:
	static GameManager* m_instance;
	StageInformation* m_stage;
	ColliderManager* m_colliderManager;
	TargetManager* m_targetManager;
	Sling* m_sling;
};
