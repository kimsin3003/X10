#ifndef __SCENE6_H__
#define __SCENE6_H__

#include "cocos2d.h"

USING_NS_CC;


class Scene6 : public Layer
{
public:

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(Scene6);

	void ChangeScene(Ref* sender);

};

#endif