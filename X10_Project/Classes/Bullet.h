#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"


class Bullet : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	void Start();
	Sprite* GetInstance();
	CREATE_FUNC(Bullet);


private:
	Sprite* bullet;
};

#endif