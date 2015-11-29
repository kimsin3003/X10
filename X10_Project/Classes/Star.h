#pragma once

class Star : public Target
{
public:
	CREATE_FUNC(Star);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

};