#pragma once

class Bullet;

class Bubble : public Target
{
public:
	virtual bool init();
	virtual void ApplyEffectToBullet(Bullet* bullet);

private:

};