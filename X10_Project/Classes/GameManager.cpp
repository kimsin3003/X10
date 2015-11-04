#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

GameManager* GameManager::GetInstance()
{
	if (instance == nullptr)
		instance = new GameManager();
	return instance;
}
