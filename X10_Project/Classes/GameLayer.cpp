#include "stdafx.h"
#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setName("GameLayer");

	return true;
}