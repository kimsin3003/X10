#pragma once

class Bullet;

class Cloud : public Target
{
public:
	CREATE_FUNC(Cloud);
	bool init();
	void ApplyEffectToBullet(Bullet* bullet);
};