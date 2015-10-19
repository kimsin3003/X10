#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;


class GameScene : public Layer
{
public:

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene);
};

#endif