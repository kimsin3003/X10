#pragma once
#include "Target.h"

class Mirror : public Target
{
public:
	CREATE_FUNC(Mirror);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	virtual void ToSelf(const Bullet* bullet);
	virtual void ToSelf(const Explosion* explosion);

};