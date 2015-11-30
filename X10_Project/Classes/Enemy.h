#pragma once
#include "Target.h"

class Enemy : public Target
{
public:
	CREATE_FUNC(Enemy);
	bool init() override;
	//Item GetItem(){ return m_item; } 곧 필요해질듯
	bool IsEnemy() { return true; }
protected:
	void ToBullet(Bullet* bullet) override;
	void ToSelf(const Bullet* bullet) override;
	void ToSelf(const Explosion* explosion) override;

};