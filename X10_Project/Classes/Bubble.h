#pragma once

class Bullet;

class Bubble : public Target
{
public:
	CREATE_FUNC(Bubble);
	virtual bool init();
	virtual void ApplyEffectToBullet(Bullet* bullet);

private:

};