#pragma once

class Cloud : public Target
{
public:
	CREATE_FUNC(Cloud);
	bool init();

private:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);
};