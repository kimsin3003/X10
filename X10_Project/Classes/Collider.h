#pragma once

class ColliderManager;

class Collider : public Node
{
public:
	virtual void Act(ColliderManager* cm) = 0;
	virtual bool IsBullet() = 0;
	bool IsFlying() { return isFlying; }

protected:
	bool isFlying;
	bool isBullet;
};