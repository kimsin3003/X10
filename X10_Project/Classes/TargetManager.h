#pragma once
class Target;
class GameManager;
class StageInformation;

class TargetManager
{
public:
	~TargetManager() { m_targets.clear(); }
	Vector<Target*>& GetTargets() { return m_targets; }; ///# 이 accessor는 필요 없다. 프렌드 클래스에서 바로 접근 가능하기 때문.
	void InitTargets(StageInformation* si);
	void ResetTargets();
	void EraseDeadTargets();
	bool HasEnemy();

private:
	Vector<Target*> m_targets;
	int m_defaultTargetNumber; //벡터 reserve 할 때 사용

	friend class GameManager;
};
