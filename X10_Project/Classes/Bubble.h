#pragma once

class Bubble : public Target
{
public:
	CREATE_FUNC(Bubble);
	bool init();

	enum{
		POP_FRAMES = 10
	};

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);
};