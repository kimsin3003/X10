#include "stdafx.h"
#include "TargetManager.h"
#include "StageInformation.h"


TargetManager::TargetManager()
{
	targets.reserve(5);
}
TargetManager::~TargetManager()
{
	targets.clear();
}

void TargetManager::InitTargets(StageInformation* si)
{

}

