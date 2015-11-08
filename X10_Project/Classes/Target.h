#pragma once
#include "stdafx.h"
class Bullet;

class Target : public Node
{
public:
	void SetEffect(Bullet* bullet);
};