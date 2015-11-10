#pragma once

class Collider : public Node
{
public:
	virtual void Act() = 0;
	virtual bool IsBullet() = 0;
	bool IsFlying() { return isFlying; }

protected:
	bool isFlying;
	bool isBullet;
};