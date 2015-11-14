#pragma once

class Bullet;

class Bubble : public Target
{
public:
	CREATE_FUNC(Bubble);
	bool init();
	const Rect& GetBoundingArea() override;

protected:

	void ToBullet(Bullet* collider) override;

	void ToExplosion(Explosion* explosion) override;

	void ToSelf(Bullet* bullet) override;

	void ToSelf(Explosion* explosion) override;

};