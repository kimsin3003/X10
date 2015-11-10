#include "stdafx.h"
#include "GameLayer.h"

GameLayer* GameLayer::createGameLayer()
{
	GameLayer* gLayer = GameLayer::create();

	return gLayer;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}