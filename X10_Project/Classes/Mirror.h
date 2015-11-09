#pragma once

class Bullet;

class Mirror : public Target
{
public:
	virtual bool init();
	virtual void ApplyEffectToBullet(Bullet* bullet);

private:

};