#pragma once
#include "Target.h"

class StageInformation;

class TargetManager
{
public:
	TargetManager();
	~TargetManager();

	Vector<Target*> GetTargets() { return targets; };
	void InitTargets(StageInformation* si);
	void EraseTarget(Target* target);

private:
	Vector<Target*> targets;
	int defaultTargetNumber;
};