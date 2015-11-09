#pragma once

class Bullet;

class Target : public Node
{
public:
	CREATE_FUNC(Target);
	virtual bool init();
	virtual void ApplyEffectToBullet(Bullet* bullet);

protected:
	Sprite* spr;
};