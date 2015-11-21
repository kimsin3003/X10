#pragma once

class ColliderManager;

class Collider : public Node
{
public:
	virtual void Act(ColliderManager* cm) = 0;
	virtual bool IsBullet() = 0;
	bool IsFlying() { return m_isFlying; }
	virtual bool ToBeErased() = 0;

protected:
	bool m_isFlying;
	bool m_isBullet;
	bool m_toBeErased;
};