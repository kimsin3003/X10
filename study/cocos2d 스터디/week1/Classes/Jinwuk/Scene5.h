#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"

USING_NS_CC;

class Scene5 : public Layer
{
public:

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(Scene5);

	void ChangeScene(Ref* sender);

};

#endif