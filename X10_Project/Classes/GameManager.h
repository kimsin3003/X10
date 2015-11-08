#pragma once
#include "Sling.h"
#include "BulletManager.h"

class GameManager
{
public:
	static GameManager* GetInstance();
	void Play();

private:
	static GameManager* instance;
	Sling* sling;
	BulletManager* bulletManager;
	GameManager();
	~GameManager();

};
