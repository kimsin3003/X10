#pragma once

class SeeBird : public Target
{
public:
	CREATE_FUNC(SeeBird);
	bool init();

protected:
	void ToBullet(Bullet* collider);
	void ToExplosion(Explosion* explosion);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

private:
	const string FILE_SEEBIRD = "res/target/SeeBird.png";
};