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

	///# 문자 리터럴은 한군데 빼서 모아 놓을 것
	const string FILE_STAR_HAPPY = "res/target/StarSad.png";
	const string FILE_STAR_SAD = "res/target/StarHappy.png";
};