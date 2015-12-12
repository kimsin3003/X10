#pragma once
#include "Target.h"

///# 네이밍 및 코딩 컨벤션
class Virtical_Mirror : public Target
{
public:
	CREATE_FUNC(Virtical_Mirror);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	virtual void ToSelf(const Bullet* bullet);
	virtual void ToSelf(const Explosion* explosion);

};

