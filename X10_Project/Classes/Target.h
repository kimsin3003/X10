#pragma once
#include "stdafx.h"
class Collider;

class Target : public Node
{
public:
	void SetEffect(Collider* collider);
	CREATE_FUNC(Target);
};