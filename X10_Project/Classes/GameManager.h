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

	void Play();
	void ShotBullet(Sling* sling);

	void SetStage(int StageNumber);

	void AppendTargetsToLayer();
	void AppendBulletsToLayer();
	Sling* InitSling();
	bool IsCollision(Target* target, Collider* collider);

	void SetUILayer(UILayer* uiLayer) { m_uiLayer = uiLayer; }
	void SetGameLayer(GameLayer* gameLayer) { m_gameLayer = gameLayer; }

private:
	GameManager();
	~GameManager();
	void CheckCollide(Collider* bullet, Vector<Target*>& targets);
	void WinProgress();
	void FailProgress();
	void ControlWinFailProgress();
	void Reset();
	void makeDebugPoint(Point p, Node* spr);

	static GameManager* m_instance;
	ColliderManager* m_colliderManager;
	TargetManager* m_targetManager;
	Sling* m_sling;
	
	int m_curStageNum;
	bool m_isJudged;
	
	UILayer* m_uiLayer;
	GameLayer* m_gameLayer;

	Vector<Sprite*> m_bulletNumUI;
};
