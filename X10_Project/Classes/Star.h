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

	const string FILE_STAR_HAPPY = "res/target/StarSad.png";
	const string FILE_STAR_SAD = "res/target/StarHappy.png";
};