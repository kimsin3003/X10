#pragma once
class Target;
class GameManager;
class StageInformation;

class TargetManager
{
public:
	~TargetManager() { m_targets.clear(); }
	void InitTargets(StageInformation* si);
	void ResetTargets();
	void EraseDeadTargets();
	bool HasEnemy();

private:
	Vector<Target*> m_targets;
	int m_defaultTargetNumber; //벡터 reserve 할 때 사용

	friend class GameManager;
};
