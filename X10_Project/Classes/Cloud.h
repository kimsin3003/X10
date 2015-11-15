#pragma once

class Bullet;

class Cloud : public Target
{
public:
	CREATE_FUNC(Cloud);
	bool init();
	const Rect& GetBoundingArea() override;


protected:

	void ToBullet(Bullet* collider) override;

	void ToExplosion(Explosion* explosion) override;

	void ToSelf(const Bullet* bullet) override;

	void ToSelf(const Explosion* explosion) override;

};