#pragma once

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

private:
	const string FILE_BUBBLE = "res/target/Bubble.png";
	const string FILE_BUBBLE_POP = "res/target/BubblePop.png";
};