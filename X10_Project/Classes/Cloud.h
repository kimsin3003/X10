#pragma once

class Bullet;

class Cloud : public Target
{
public:
	virtual bool init();
	virtual void ApplyEffectToBullet(Bullet* bullet);

private:

};