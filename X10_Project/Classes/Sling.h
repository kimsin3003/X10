#ifndef __SLING_H__
#define __SLING_H__

#include "Bullet.h"

class Sling : public cocos2d::Layer
{
public:
	Sling();
	void Shot();
	void initSling();

	//mouse listener
	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	bool isPressed = false;

	Point posStartClick;
	Sprite* Stick;
	Sprite* Shooter;

	Point angle; // 0~180
	float power;

	enum { ShooterUIBoundary = 100 };
};

#endif