#pragma once
class Target;
class GameManager;
class StageInformation;

class TargetManager
{
public:
	///# 생성자는 어디? 멤버 초기화는 어디서?

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
