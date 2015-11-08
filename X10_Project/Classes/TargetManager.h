#pragma once
#include "Target.h"

class TargetManager
{
public:
	static TargetManager* GetInstance();
	vector<Target*> GetTargets() { return targets; }
private:
	static TargetManager* instance;
	vector<Target*> targets;
	TargetManager();
	~TargetManager();
};

