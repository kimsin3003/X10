#pragma once

class Cloud : public Target
{
public:
	CREATE_FUNC(Cloud);
	bool init();

private:
	void ToBullet(Bullet* collider);
	void ToExplosion(Explosion* explosion);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

	const string FILE_CLOUD = "res/target/Cloud.png";
	const string FILE_CLOUD_LEFT = "res/target/CloudLeft.png";
	const string FILE_CLOUD_RIGHT = "res/target/CloudRight.png";

	bool applyEffectToMe;
};