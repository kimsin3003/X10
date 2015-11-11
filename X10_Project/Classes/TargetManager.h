#pragma once
#include "Target.h"
class StageInformation;

class TargetManager
{
public:
	static TargetManager* GetInstance();
	Vector<Target*> GetTargets() { return targets; };
	void InitTargets(StageInformation* stage);

private:
	static TargetManager* instance;
	Vector<Target*> targets;
	TargetManager();
	~TargetManager();
};

