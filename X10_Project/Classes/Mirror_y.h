#pragma once
#include "Target.h"

///# ���̹� �� �ڵ� ������ (���� ������ ������ ���� �ƴ� �� ����.. under_score vs CamelCase )
class Mirror_y : public Target
{
public:
	CREATE_FUNC(Mirror_y);
	bool init();

protected:
	void ToBullet(Bullet* bullet);
	virtual void ToSelf(const Bullet* bullet);
	virtual void ToSelf(const Explosion* explosion);

};

