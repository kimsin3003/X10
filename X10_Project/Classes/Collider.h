#pragma once

class Collider : public Node
{
public:
	virtual void Act() = 0;
	virtual bool IsFlying() =0;
};