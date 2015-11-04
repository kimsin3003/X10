#pragma once
#include "Target.h"

class Enemy : public Target
{
private:
	float hp;
public:
	void getHp();
};