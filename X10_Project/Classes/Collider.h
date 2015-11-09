#pragma once

class Collider : public Node
{
public:
	virtual void Act() = 0;
	virtual bool IsFlying() = 0;
	virtual bool IsBullet() = 0;
	virtual bool IsAlive() = 0;

protected:
	bool isAlive;
};