#pragma once
#include "Target.h"

class Enemy : public Target
{
public:
	void getHp(); 
private:
	float hp;
};