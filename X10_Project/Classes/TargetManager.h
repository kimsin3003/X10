#pragma once
class Target;
class GameManager;
class StageInformation;

class TargetManager
{
public:
	TargetManager() {}
	~TargetManager() {}
	Vector<Target*> GetTargets() { return m_targets; };
	void InitTargets(StageInformation* si);
	void ResetTargets();
	void EraseTarget(Target* target);

private:
	Vector<Target*> m_targets;
	int m_defaultTargetNumber; //벡터 reserve 할 때 사용

	friend class GameManager;
};