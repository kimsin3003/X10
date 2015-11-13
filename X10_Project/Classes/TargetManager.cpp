#include "stdafx.h"
#include "TargetManager.h"
#include "StageInformation.h"

#include "Mirror.h"

TargetManager::TargetManager()
{
	currentTargetIdx = 0;
	defaultTargetNumber = 1;
	targets.reserve(defaultTargetNumber);
}
TargetManager::~TargetManager()
{
	targets.clear();
}

void TargetManager::InitTargets(StageInformation* si)
{
	targets.pushBack(Mirror::create());
}

