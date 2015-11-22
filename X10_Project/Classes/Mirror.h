#pragma once

class Mirror : public Target
{
public:
	CREATE_FUNC(Mirror);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

	const string FILE_MIRROR = "res/target/Mirror.png";
	const string FILE_MIRROR_ANGRY = "res/target/MirrorAngry.png";
};