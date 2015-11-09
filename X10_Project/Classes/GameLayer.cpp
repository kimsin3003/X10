#include "stdafx.h"
#include "GameLayer.h"

GameLayer* GameLayer::createGameLayer()
{
	GameLayer* gLayer = GameLayer::create();
	return gLayer;
}

bool GameLayer::init()
{
	if (Layer::init() == false)
		return false;

	setAnchorPoint(Vec2(0, 0));

	return true;
}