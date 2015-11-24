#include "stdafx.h"
#include "GameLayer.h"

/* 
///#필요도 없으면서!
GameLayer* GameLayer::createGameLayer()
{
	GameLayer* gLayer = GameLayer::create();
	
	return gLayer;
}
*/
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setName("GameLayer");

	return true;
}