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

	void SetStage(GameLayer* gameLayer, UILayer* uiLayer, int StageNumber);

	void AppendTargetsToLayer(GameLayer* gameLayer);
	void AppendBulletsToLayer(UILayer* uiLayer);
	Sling* InitSling(GameLayer* gameLayer);
	bool IsCollision(Target* target, Collider* collider);

private:
	GameManager();
	~GameManager();
	void CheckCollide(Collider* bullet, Vector<Target*>& targets);
	void WinProgress(UILayer* uiLayer);
	void FailProgress(UILayer* uiLayer);
	void ControlWinFailProgress(UILayer* uiLayer);
	void Reset();
	void makeDebugPoint(Point p, Node* spr);

	static GameManager* m_instance;
	ColliderManager* m_colliderManager;
	TargetManager* m_targetManager;
	Sling* m_sling;
	
	int m_curStageNum;
	bool m_isJudged;
	Vector<Sprite*> m_bulletNumUI;
};
