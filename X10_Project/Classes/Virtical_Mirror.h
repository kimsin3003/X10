#pragma once

///# Vertical... typo??
class Virtical_Mirror : public Target
{
public:
	CREATE_FUNC(Virtical_Mirror);

	//virtual const Rect GetBoundingArea() override;
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);

};

