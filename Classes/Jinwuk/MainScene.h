#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;


class MainScene : public Layer
{
public:

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(MainScene);

	void ChangeScene(Ref* sender);
};

#endif