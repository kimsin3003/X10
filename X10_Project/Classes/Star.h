#pragma once

class Star : public Target
{
public:
	CREATE_FUNC(Star);
	bool init();

	enum 
	{
		DESTRUCT_FRAMES = 9
	};
protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);
};