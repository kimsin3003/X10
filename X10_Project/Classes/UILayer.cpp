#include "stdafx.h"
#include "UILayer.h"

UILayer* UILayer::createUILayer()
{
	UILayer* IU = UILayer::create();
	return IU;
}

bool UILayer::init()
{
	if (Layer::init() == false)
		return false;

	return true;
}