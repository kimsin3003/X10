#pragma once
#include "Target.h"

class Enemy : public Target
{
	///# private / public 순서 코딩 컨벤션 정하고, 멤버 변수가 있는한 생성자안에서 초기화 하는 습관을..
private:
	float hp;
public:
	void getHp();
};