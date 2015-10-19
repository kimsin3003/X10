#ifndef __MY_SCENE_H__
#define __MY_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class myScene : public Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(myScene);
	virtual bool init();
};
#endif