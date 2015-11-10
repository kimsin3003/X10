#pragma once

class Bullet;

class Bubble : public Target
{
public:
	CREATE_FUNC(Bubble);
	bool init();
	void ApplyEffectToBullet(Bullet* bullet);
};