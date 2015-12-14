#pragma once

class Collider : public Node
{
public:
	virtual void Act() = 0;
	virtual bool IsBullet() = 0;
	bool IsFlying() { return m_isFlying; }
	void SetFlying(bool flag) { m_isFlying = flag; }
	bool ToBeErased() { return m_toBeErased; }
protected:
	bool m_isFlying;
	bool m_toBeErased;
};