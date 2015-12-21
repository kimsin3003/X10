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
	void SaveEnemyPosition(const Point& pos);
	Point GetEnemyPosition() { return m_enemyPosition; }

private:
	Vector<Target*> m_targets;
	int m_defaultTargetNumber;
	Point m_enemyPosition;
	friend class GameManager;
};
