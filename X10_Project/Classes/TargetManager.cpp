#include "stdafx.h"
#include "TargetManager.h"

TargetManager::TargetManager() {}
TargetManager::~TargetManager() {}

TargetManager* TargetManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new TargetManager();
	}
	return instance;
}