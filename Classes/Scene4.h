#pragma once
#include "cocos2d.h"
#include "cocos2d\cocos\2d\CCLayer.h"
class Scene4 :
	public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(Scene4);
};

