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
	int m_defaultTargetNumber;
	friend class GameManager;
};
