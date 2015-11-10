#pragma once

class Bullet;

class Mirror : public Target
{
public:
	CREATE_FUNC(Mirror);
	bool init();
	void ApplyEffectToBullet(Bullet* bullet);
};