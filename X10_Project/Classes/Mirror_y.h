#pragma once
#include "Target.h"

///# 네이밍 및 코딩 컨벤션 (밑줄 쓰려면 끝까지 쓰고 아님 다 빼고.. under_score vs CamelCase )
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

