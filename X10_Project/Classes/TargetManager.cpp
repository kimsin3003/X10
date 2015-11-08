#include "stdafx.h"
#include "TargetManager.h"

TargetManager::TargetManager() {}
TargetManager::~TargetManager() {}

TargetManager* TargetManager::instance = nullptr;

TargetManager* TargetManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TargetManager();
	}
	return instance;
}