#pragma once
#include "Target.h"

class TargetManager
{
public:
	static TargetManager* GetInstance();
	Vector<Target*> GetTargets() { return targets; }
private:
	static TargetManager* instance;
	Vector<Target*> targets;
	TargetManager();
	~TargetManager();
};

