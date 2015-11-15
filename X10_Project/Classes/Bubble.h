#pragma once

class Bullet;

class Bubble : public Target
{
public:
	CREATE_FUNC(Bubble);
	bool init();

protected:
	void ToBullet(Bullet* collider);
	void ToExplosion(Explosion* explosion);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);
};