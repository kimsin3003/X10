#pragma once
#include "Target.h"

///# 네이밍 및 코딩 컨벤션
class Mirror_y : public Target
{
public:
	CREATE_FUNC(Mirror_y);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	virtual void ToSelf(const Bullet* bullet);
	virtual void ToSelf(const Explosion* explosion);

	const string FILE_MIRROR = "res/target/flat_mirror.png";
};

