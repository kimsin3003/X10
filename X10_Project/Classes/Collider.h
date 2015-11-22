#pragma once

class ColliderManager;

class Collider : public Node
{
public:
	virtual void Act() = 0;
	virtual bool IsBullet() = 0;
	bool IsFlying() { return m_isFlying; }
	bool ToBeErased() {	return m_toBeErased; }
	void SetFlying(bool flag) { m_isFlying = flag; }
protected:
	bool m_isFlying;
	bool m_isBullet;
	bool m_toBeErased;
};