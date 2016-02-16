#ifndef MIRROR_H
#define MIRROR_H

class Mirror : public Target
{
public:
	CREATE_FUNC(Mirror);
	bool init();
	bool IsMirror() { return true; }

protected:
	void ToBullet(Bullet* bullet);
	void ToSelf(const Bullet* bullet);
	void ToSelf(const Explosion* explosion);
};

#endif