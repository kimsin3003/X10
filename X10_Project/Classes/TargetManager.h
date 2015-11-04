#pragma once
class TargetManager
{
public:
	TargetManager* GetInstance();

private:
	TargetManager* instance;
	TargetManager();
	~TargetManager();
};

