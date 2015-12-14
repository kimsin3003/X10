#pragma once
#include "stdafx.h"
class GameLayer;
class UILayer;
class StageInformation;
class ColliderManager;
class TargetManager;
class CollectionManager;
class Collider;
class Target;
class Sling;

class GameManager
{
public:
	static GameManager* GetInstance();

	void Play(GameLayer* gameLayer, UILayer* uiLayer);
	void ShotBullet(Sling* sling);

	void SetStage(GameLayer* gameLayer, int StageNumber);

	void AppendTargetsToLayer(GameLayer* gameLayer);
	Sling* SetSling(GameLayer* gameLayer);

private:
	GameManager();
	~GameManager();
	void CheckCollide(Collider* bullet, Vector<Target*>& targets);
	void WinProgress(UILayer* uiLayer);
	void EarnCollectionEvent(UILayer* uiLayer);
	void FailProgress(UILayer* uiLayer);
	void ControlWinFailProgress(UILayer* uiLayer);
	void EnemyDyingEffect();
	void SetCollectionPos(const Vec2& pos);
	void Reset();

	static GameManager* m_instance;
	ColliderManager* m_colliderManager;
	TargetManager* m_targetManager;
	CollectionManager* m_collectionManager;
	Sling* m_sling;
	Sprite* m_curCollection;
	
	int m_stage;
	bool m_isJudged;
};
