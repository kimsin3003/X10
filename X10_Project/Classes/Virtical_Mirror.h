#pragma once
#include "Target.h"

///# ���̹� �� �ڵ� ������
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

