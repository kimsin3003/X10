#include "stdafx.h"
#include "TargetManager.h"

TargetManager* TargetManager::instance = nullptr;

TargetManager* TargetManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TargetManager();
	}
	return instance;
}

TargetManager::TargetManager()
{
	targets.reserve(5);
}
TargetManager::~TargetManager() {}

