#ifndef __SLING_H__
#define __SLING_H__

#include "Bullet.h"

class Sling : public Node
{
public:
	static Sling* createSling(Bullet* bullet);
	CREATE_FUNC(Sling);
	virtual bool init();

	void onMouseDown(cocos2d::Event* event);
	void onMouseUp(cocos2d::Event* event);
	void onMouseMove(cocos2d::Event* event);
	
	bool IsShooted() { return isShooted; }
	bool isShooted;

	bool IsPressed() { return isPressed; }
	bool isPressed;

	Point posStartClick;
	
	Sprite* Stick;
	Sprite* Shooter;

	Point angle;
	float power;

	enum { ShooterUIBoundary = 100 };
};

#endif